/*                               -*- Mode: C -*- 
 * 
 * Filename: tga.h
 * Description: 
 * Author: Lunacie
 * Created: Thu Oct  1 17:15:04 2015 (+0200)
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


#ifndef			TAG_H
#define			TAG_H

// Header to determine file type
typedef struct		s_tgaHeader
{
  GLubyte		header[12];
}			t_tgaHeader;



// Can be casted as a t_texture  
typedef struct		s_tga
{
  // == Shared t_texture content ==========================

  GLuint		type;			// GL_RGB/GL_RGBA

  int			bitsPerPixel;		// 24 or 32

  int			height;
  int			width;


  unsigned int		T_TEXTURE_id;
  GLubyte		*T_TEXTURE_imageData;


  // == TGA ONLY CONTENT STARTS HERE ========================
  GLubyte		header[6];		// The first 6 bytes are useful
  int			bytesPerPixel;
  int			imageSize;		// In memory
  
}			t_tga;



t_texture		*loadTGA(char * fileName);

static t_texture	*loadUncompressedTGA(char *fileName, FILE *file, t_texture *texture);
static t_texture	*loadCompressedTGA(char *fileName, FILE *file, t_texture *texture);

static t_tga		*loadHeaderData(FILE *file, t_tga *tga);

#endif			/* TAG_H */
