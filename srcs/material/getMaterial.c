/*                               -*- Mode: C -*- 
 * 
 * Filename: material.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Jan 24 17:55:36 2015 (+0100)
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


t_material			*getMaterial(char *name, char *prefix)
{
  t_material			*material;
  FILE			*file;
  char			*path;
  char			tmp[1024];

  material = NULL;

  if (!(path = getFilePath(name, prefix, MATERIAL)))
    return raise_e(ERROR, CANT_PATH_MATERIAL, NULL, "getMaterial#1 - material.c");
  /* snprintf(tmp, 1024, "%s - getMaterial#2 - material.c", path); */


  if (!(file =  fopen(path, "r")))
    return raise_e(WARNING, NULL, NULL, path);
  free(path);


  if (!(material = malloc(sizeof(t_material))))
    {
      fclose(file);
      return raise_e(ERROR, NULL, NULL, "malloc() -  getMaterial() - material.c");
    }
  memset(material, 0, sizeof(material));
  material->name = name;

  if (!(material = fillMaterial(file, material)))
    {
      fclose(file);
      return raise_e(ERROR, CANT_FILL_MATERIAL, NULL, "getMaterial#3 - material.c");
    }
  fclose(file);
  return material;
}




static t_material		*fillMaterial(FILE *file, t_material *material)
{
  char			 buffer[1024];
  size_t		x;

  // Init
  for (x = 0; x < _TEXTUREMAPTYPE_SIZE; x++)
    material->textureMaps[x].filePath = NULL;

  // Reading Material File
  while (fgets(buffer, 1024, file))
    {
      // DiffuseMap
      if (!strncmp(buffer, DIFFUSE_MAP_STR, strlen(DIFFUSE_MAP_STR))) 
	{
	  if (sscanf(buffer, DIFFUSE_MAP_STR"%ms\n", &material->textureMaps[DIFFUSE].fileName))
	    {
	      if (addNewTextureMap(material, DIFFUSE) == FAILURE);
	      else
		debug("| | | |  | | | | New Diffuse Map : %s\n", material->textureMaps[DIFFUSE].filePath);
	    }
	}
      /* printf("late while\n"); */
    }
  return material;
}

