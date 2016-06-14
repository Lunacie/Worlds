/*                               -*- Mode: C -*- 
 * 
 * Filename: textureMap.h
 * Description: 
 * Author: Lunacie
 * Created: Tue Sep 29 19:34:56 2015 (+0200)
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


#ifndef			TEXTUREMAP_H
#define			TEXTUREMAP_H

#define			DIFFUSE_MAP_STR		"map_Kd "

typedef			enum
  {
    AMBIANT = 0,
    DIFFUSE,
    SPECULAR,
    
    _TEXTUREMAPTYPE_SIZE
  }			e_textureMapType;

typedef struct		s_textureMap
{
  e_textureMapType	type;
  
  unsigned int		id;
  char			*filePath;
  char			*fileName;
  struct s_texture	*data;
}			t_textureMap;


// Texture structure usable by onpenGL
typedef struct		s_texture
{
  
  int			type;			// type of data stored in imageData (GL_RGB, GL_RGBA)

  int			bpp;			// bits per pixels

  int			width;
  int			height;

  unsigned int		id;			// texture ID for glBindTexture
  GLubyte		*imageData;		// Color Values
  
}			t_texture;



#endif			/* TEXTUREMAP_H */
