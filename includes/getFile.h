/*                               -*- Mode: C -*- 
 * 
 * Filename: getFile.h
 * Description: 
 * Author: Lunacie
 * Created: Tue Sep 29 02:03:47 2015 (+0200)
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

#ifndef			GETFILE_H
#define			GETFILE_H

typedef	enum
  {
    OBJ = 0,
    MATERIAL,
    TEXTURE_MAP,

    _FILETYPE_SIZE
  }			e_fileType;

typedef	struct		s_fileData
{
  e_fileType		type;
  char			*directory;
  char			*sufix;
}			t_fileData;

#define			ASSETS_DIR		"/assets"

char			*getFilePath(char *name, char *prefix, e_fileType);

#endif			/* GETFILE_H */
