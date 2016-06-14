/*                               -*- Mode: C -*- 
 * 
 * Filename: textureMap.c
 * Description: 
 * Author: Lunacie
 * Created: Wed Sep 30 19:46:10 2015 (+0200)
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
#include		"material.h"
#include		"textureMap.h"
#include		"list.h"
#include		"handle_error.h"
#include		"getFile.h"
#include		"tga.h"


int			addNewTextureMap(t_material *material, e_textureMapType type)
{
  static size_t		totalTextureMapNb = 0;
  char			*fileName;

  t_texture		*texture;

  fileName = material->textureMaps[type].fileName;
  if (!(material->textureMaps[type].filePath = getFilePath(fileName, "cat/", type)))
    return FAILURE;
  material->textureMaps[type].type = type;
  material->textureMaps[type].id = totalTextureMapNb;

  if ((texture = loadTGA(material->textureMaps[type].filePath)))
    {
      material->textureMaps[type].data = texture;
      loadGLTexture(texture);
      debug("| | | |  | | | | %s : TGA texture map succesfully loaded\n", fileName);
      totalTextureMapNb += 1;
    }
  else
    {
      debug("| | | |  | | | | %s : Could not load texture map\n", fileName);
      return FAILURE;
    }
  return 0;
} 

int			loadGLTexture(t_texture *texture)
{
  glGenTextures(1, &(texture->id));

  glBindTexture(GL_TEXTURE_2D, texture->id);

  glTexImage2D(GL_TEXTURE_2D, 0, texture->type, texture->width, texture->height, 0,
  	       GL_BGR_EXT, GL_UNSIGNED_BYTE, texture->imageData);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
