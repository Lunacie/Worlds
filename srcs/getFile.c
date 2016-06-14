/*                               -*- Mode: C -*- 
 * 
 * Filename: getFile.c
 * Description: 
 * Author: Lunacie
 * Created: Tue Sep 29 02:02:45 2015 (+0200)
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
#include		"getFile.h"
#include		"handle_error.h"


t_fileData		fileData[_FILETYPE_SIZE] = 
  {
    {OBJ, "/models", ".obj"},
    {MATERIAL, "/models", ""},
    {TEXTURE_MAP, "/models", ""},
  };

char		*getFilePath(char *name, char *prefix, e_fileType type)
{
  char			*path;
  char			*sufix;
  char			*directory;
  static char		*cwd = NULL;

  if (!cwd)
    {
      cwd = malloc(128);
      if (!(cwd = getcwd(cwd, 128)))
	return raise_e(ERROR, NULL, NULL, "getcwd() - getObjPath() - obj.c");
    }
      

  if (!(path = malloc(1024)))
    return raise_e(ERROR, NULL, NULL, "malloc() - getObjPath - obj.c");
  if (!prefix)
    prefix = "";

  sufix = fileData[type].sufix;
  directory = fileData[type].directory;

  if (snprintf(path, 1024, "%s%s%s/%s%s%s", cwd, ASSETS_DIR, directory, prefix, name, sufix) <= 0)
    return raise_e(ERROR, SNPRINTF_FAILED, NULL, "snprintf() - getObjPath - obj.c");


      /* if (!(realpath(*current, *current))) */
      /* 	return raise_e(ERROR, NULL, NULL, "realpath() - getObjPath() - obj.c"); */
  return path;
}
