/*                               -*- Mode: C -*- 
 * 
 * Filename: obj.h
 * Description: 
 * Author: Lunacie
 * Created: Sat Jan 24 17:56:08 2015 (+0100)
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


#ifndef			OBJ_H
#define			OBJ_H

#include		"graphicEngine.h"
#include		"list.h"
#include		"material.h"

typedef			enum
  {
    TRIS,
    QUADS
  }			e_faceType;

typedef			struct s_obj
{
  t_list		*v;
  t_list		*vn;
  t_list		*vt;
  t_list		*faces;

  char			*texture;
  char			*materialName;

  size_t		nb_faces;
  size_t		nb_v;
  size_t		nb_vt;
  size_t		nb_vn;


  t_list		*materials;
 
  e_faceType		faceType;

  // s off ??
}			t_obj;


/* 
** Drawing the OBJ
*/



/* 
** Getting the OBJ
*/

t_obj			*getObj(char *name, char *prefix, e_faceType);

static char		*resolveName(char *str, char*path);
static t_obj		*fillObj(FILE *file, t_obj *obj);
static void		cutFaceString(t_faceVertex *faceVertex, t_obj *obj);
static t_vertex		*getVertexFromID(int id, t_list *list);
static void		initObj(t_obj **obj);

#endif			/* OBJ_H */
