/*                               -*- Mode: C -*- 
 * 
 * Filename: tga.c
 * Description: 
 * Author: Lunacie
 * Created: Thu Oct  1 17:14:52 2015 (+0200)
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * 
 */

/* Change Log:
 * 
 * 
 * 
 */

#include		"graphicEngine.h"
#include		"list.h"
#include		"handle_error.h"
#include		"textureMap.h"
#include		"tga.h"


/*
** These are an UNCOMPRESSED TGA Header's first 12 byte : 
** 0 0 2 0 0 0 0 0 0 0 0 0
*/
GLubyte		tga_uncompressed[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
** These are a RLE COMPRESSED TGA Header's first 12 byte : 
** 0 0 10 0 0 0 0 0 0 0 0 0
*/
GLubyte		tga_compressed[12] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};


t_texture		*loadTGA(char * fileName)
{
  t_tgaHeader		header;			// file header
  t_tga			tga;			// file data
  
  FILE			*file;
  t_texture		*texture;


  if (!(file =  fopen(fileName, "rb")))
    return raise_e(WARNING, NULL, NULL, fileName);

  texture = NULL;
  // Careful to malloc sizeof tga so that it can be cast into a bigger struct
  if (!(texture = malloc(sizeof(t_tga))))
    {
      fclose(file);
      return raise_e(ERROR, NULL, NULL, "malloc() -  loadTGA() - tga.c");
    }
  memset(texture, 0, sizeof(t_texture));
  

  // Read 1x12 bytes and stores them into header
  if (!(fread(&header, sizeof(t_tgaHeader), 1, file)))
    {
      fclose(file);
      free(texture);
      return raise_e(ERROR, NULL, NULL, "fread() -  loadTGA() - tga.c");
    }
  
  // Check header compressed or not and loads
  if (!memcmp(tga_uncompressed, &header, sizeof(t_tgaHeader)))
    texture = loadUncompressedTGA(fileName, file, texture);
  else if (!memcmp(tga_compressed, &header, sizeof(t_tgaHeader)))
    texture = loadCompressedTGA(fileName, file, texture);
  else // Else, file is invalid
    {
      fclose(file);
      free(texture);
      return raise_e(WARNING, INVALID_TGA, NULL, "loadTGA() - tga.c");
    }
  
  fclose(file);
  return texture;
}


/* First 18 bytes of a TGA file: 
**
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;

   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
**
*/


static t_tga		*loadHeaderData(FILE *file, t_tga *tga)
{
  // read first 6 bytes (x1) and store them into tga->header
  if (!(fread(tga->header, sizeof(tga->header), 1, file)))
    {
      free(tga);
      return raise_e(ERROR, NULL, NULL, "fread()#1 -  loadHeaderData() - tga.c");
    }
  
  tga->width = (tga->header[1] * 256) + tga->header[0];
  tga->height = (tga->header[3] * 256) + tga->header[2];
  tga->bitsPerPixel = tga->header[4];
 
  // width and height need to be at least 1px and bpp needs to be 32 or 24
  if (tga->width < 1 || tga->height < 1 ||
      (tga->bitsPerPixel != 32 && tga->bitsPerPixel != 24))
    {
      free(tga);
      return raise_e(WARNING, INVALID_TGA_HEADER, NULL, "loadHeaderData() - tga.c");
    }
  if (tga->bitsPerPixel == 24)
    tga->type = GL_RGB;
  else  /* if (tga->bitsPerPixel == 32) */
    tga->type = GL_RGBA;
  
  tga->bytesPerPixel = (tga->bitsPerPixel / 8);
  tga->imageSize = tga->bytesPerPixel * tga->width * tga->height;

  return tga;
}

static t_texture	*loadUncompressedTGA(char *fileName, FILE *file, t_texture *texture)
{
  t_tga			*tga;
  size_t		x;

  debug("| | | |  | | | | | %s is an UNcompressed TGA file\n", fileName);

  tga = (t_tga *)(texture);

  if (!(tga = loadHeaderData(file, tga)))
    return NULL;

  // allocating memory for the image
  if (!(tga->T_TEXTURE_imageData = (GLubyte *)malloc(tga->imageSize)))
    {
      free(texture);
      return raise_e(ERROR, NULL, NULL, "malloc() - loadUncompressedTGA() - tga.c");
    }

    
  // read all the image
  if (!(fread(tga->T_TEXTURE_imageData, tga->imageSize, 1, file)))
    {
      free(tga->T_TEXTURE_imageData);
      free(texture);
      return raise_e(WARNING, NULL, NULL, "fread()#2 -  loadUncompressedTGA() - tga.c");
    }


  // TGA storage format is BGR =>  switching to RGB usign binary operation on each pixel
  /* for (x = 0; x < tga->imageSize; x += tga->bytesPerPixel) */
  /*   { */
  /*     // 1st Byte XOR 3rd Byte XOR 1st Byte XOR 3rd Byte */
  /*     texture->imageData[x] ^= texture->imageData[x + 2] ^= */
  /* 	texture->imageData[x] ^= texture->imageData[x +2]; */
  /*   } */

  return texture;
} 

static t_texture	*loadCompressedTGA(char *fileName, FILE *file, t_texture *texture)
{
  t_tga			*tga;
  size_t		x;

  int			pixelCount;
  int			currentPixel;
  int			currentByte;

  GLubyte		*colorBuffer;

  debug("| | | |  | | | | | %s is a compressed TGA file\n", fileName);

  if (!(tga = loadHeaderData(file, tga)))
    return NULL;

  // allocating memory for the image
  if (!(tga->T_TEXTURE_imageData = (GLubyte *)malloc(tga->imageSize)))
    {
      free(texture);
      return raise_e(ERROR, NULL, NULL, "malloc()#1 - loadCompressedTGA() - tga.c");
    }
  
  pixelCount = tga->height * tga->width;
  currentPixel = 0;
  currentByte = 0;

  if (!(colorBuffer = (GLubyte *)malloc(tga->bytesPerPixel)))
    {
      free(tga->T_TEXTURE_imageData);
      free(texture);
      return raise_e(ERROR, NULL, NULL, "malloc()#2 - loadCompressedTGA() - tga.c");
    }
  
  /* 
     See this tutorial for compressed tga implementation
     http://nehe.gamedev.net/tutorial/loading_compressed_and_uncompressed_tga%27s/22001/
  */

  return texture;
} 
