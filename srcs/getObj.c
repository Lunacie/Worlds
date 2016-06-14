/*                               -*- Mode: C -*- 
 * 
 * Filename: obj.c
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
#include		"obj.h"
#include		"list.h"
#include		"handle_error.h"
#include		"getFile.h"


extern			char *binary;

t_obj			*getObj(char *name, char *prefix, e_faceType faceType)
{
  t_obj			*obj;
  FILE			*file;
  char			*path;
  char			tmp[1024];

  obj = NULL;
  if (!(path = getFilePath(name, prefix, OBJ)))
    return raise_e(ERROR, CANT_PATH_OBJ, NULL, "getObj#1 - obj.c");

  snprintf(tmp, 1024, "%s - getObj#2 - obj.c", path);
  if (!(file =  fopen(path, "r")))
    return raise_e(ERROR, CANT_OPEN_OBJ, NULL, tmp);
  free(path);


  if (!(obj = malloc(sizeof(t_obj))))
    {
      fclose(file);
      return raise_e(ERROR, MALLOC_FAILED, NULL, "getObj#3 - obj.c");
    }
  memset(obj, 0, sizeof(obj));

  if (!(obj = fillObj(file, obj)))
    {
      fclose(file);
      return raise_e(ERROR, CANT_FILL_OBJ, NULL, "getObj#3 - obj.c");
    }
    
  obj->faceType = faceType;
  debug("| | | |  | Object was filled with content");

  fclose(file);
  return obj;
}



static void		initObj(t_obj **obj)
{
  (*obj)->v = NULL;
  (*obj)->nb_v = 0;

  (*obj)->vn = NULL;
  (*obj)->nb_vn = 0;

  (*obj)->vt = NULL;
  (*obj)->nb_vt = 0;

  (*obj)->faces = NULL;
  (*obj)->nb_faces = 0;

  (*obj)->materials = NULL;
  (*obj)->materialName = NULL;
}

static t_obj		*fillObj(FILE *file, t_obj *obj)
{
  char			 buffer[1024];
  int			rc;
  size_t		x;

  t_vertex		*vertex;
  t_uv			*texel;
  t_face		*face;
  

  initObj(&obj);
  while (fgets(buffer, 1024, file))
    {

      if (!strncmp(buffer, "v ", 2)) // Vertex
	{
	  vertex = NULL;
	  if (!(vertex = malloc(sizeof(t_vertex))))
	    return raise_e(ERROR, MALLOC_FAILED, NULL, "fillObj - vertex - obj.c");
	  if (sscanf(buffer, "v %f %f %f\n", &vertex->x, &vertex->y, &vertex->z))
	    {
	      obj->nb_v += 1;
	      vertex->id = obj->nb_v;
	      /* debug("| | | |  | | New vertex : %d (%f, %f, %f)", obj->nb_v, vertex->x,  vertex->y,  vertex->z); */
	      obj->v = addToList(obj->v, vertex);
	    }
	}


      else if (!strncmp(buffer, "vn ", 3)) // Vertex normal
	{
	  vertex = NULL;
	  if (!(vertex = malloc(sizeof(t_vertex))))
	    return raise_e(ERROR, MALLOC_FAILED, NULL, "fillObj - vertex normal - obj.c");
	  if (sscanf(buffer, "vn %f %f %f\n", &vertex->x, &vertex->y, &vertex->z))
	    {
	      obj->nb_vn += 1;
	      vertex->id = obj->nb_vn;
	      debug("| | | |  | | New vertex normal : %d (%f, %f, %f)",
	      	    obj->nb_v, vertex->x,  vertex->y,  vertex->z);
	      obj->vn = addToList(obj->vn, vertex);
	    }
	}


      else if (!strncmp(buffer, "vt ", 3)) // Vertex Texture
	{
      	  texel = NULL;
      	  if (!(texel = malloc(sizeof(t_uv))))
      	    return raise_e(ERROR, MALLOC_FAILED, NULL, "fillObj - vertex texture - obj.c");
      	  if (sscanf(buffer, "vt %f %f\n", &texel->x, &texel->y))
	    {
	      obj->nb_vt += 1;
	      texel->id = obj->nb_vt;
      	      debug("| | | |  | | New vertex texture : %d (%f, %f)",
      		    obj->nb_vt, texel->x,  texel->y);
	      obj->vt = addToList(obj->vt, texel);
	    }
	}

      
      else if (!strncmp(buffer, "f ", 2)) // Face
      	{
      	  face = NULL;
      	  if (!(face = malloc(sizeof(t_face))))
      	    return raise_e(ERROR, MALLOC_FAILED, NULL, "fillObj - face - obj.c");
      	  if (sscanf(buffer, "f %s %s %s\n",
		     &face->faceVertex[0].str, &face->faceVertex[1].str, &face->faceVertex[2].str) == 3 &&
	      *face->faceVertex[0].str != '\0' && *face->faceVertex[1].str != '\0' && *face->faceVertex[2].str != '\0')
      	    {
      	      obj->nb_faces += 1;
      	      debug("| | | |  | | New Face : %d (%s, %s, %s)",
	      	    obj->nb_faces, face->faceVertex[0].str, face->faceVertex[1].str, face->faceVertex[2].str);
	      for (x = 0; x < 3; x++)
		cutFaceString(&(face->faceVertex[x]), obj);
	      obj->faces = addToList(obj->faces, face);
      	    }
      	}

      else if (!strncmp(buffer, "mtllib ", strlen("mtllib "))) // Material
      	{
	      if (sscanf(buffer, "mtllib %ms\n", &(obj->materialName)))
      	    {
      	      debug("| | | |  | | New Material : %s", obj->materialName);
      	      // Several material per obj
      	      /* obj->v = addToList(obj->v, vertex); */
      	    }
      	}





      
    }
  printf("| | | |  | Nb Vertex : %d \n", obj->nb_v);
  printf("| | | |  | Nb Normals : %d \n", obj->nb_vn);
  printf("| | | |  | Nb Vertex texture : %d \n", obj->nb_vt);
  printf("| | | |  | Nb Faces : %d \n", obj->nb_faces);
  return obj;
}

static void		cutFaceString(t_faceVertex *faceVertex, t_obj *obj)
{
  char *str;
  char *tmp;

  char *v = NULL;
  char *vn = NULL;
  char *vt = NULL;

  int	int_v = 0;
  int	int_vt = 0;
  int	int_vn = 0;

  if (!(str = strdup(faceVertex->str)))
    return;
  tmp = str;
  /* printf("%s : ", str); */
  v = str;
  while (*str && *str != '/')
    str++;
  if (*str && *(str + 1) != '/')
    {
      vt = str + 1;
      *str = '\0';
      str++;
    }
  while (*str && *str != '/')
    str++;
  if (*str)
    {
      vn = str + 1;
      *str = '\0';
      str++;
    }
  if (v)
    int_v = atoi(v);
  if (vt)
    int_vt = atoi(vt);
  if (vn)
    int_vn = atoi(vn);

  /* printf("Vertice : %d\n", int_v); */


  free(tmp);
  faceVertex->v = getVertexFromID(int_v, obj->v);
  faceVertex->vn = getVertexFromID(int_vn, obj->vn);
  faceVertex->vt = getVertexFromID(int_vt, obj->vt);
  /* printf("id is : %d\n", int_vt); */

  debug("| | | |  | | | Face Vertex id : (%d)", int_v);
  debug("| | | |  | | | Face Vertex normal id : (%d)", int_vn);
  debug("| | | |  | | | Face Texel id : (%d)", int_vt);
  /* exit(0); */
  /* face->vt = int_vt; */
}



static t_vertex		*getVertexFromID(int id, t_list *list)
{
  while (list)
    {
      if (list->content)
	{
	  if (((t_vertex *)list->content)->id == id)
	    return list->content;
	}
      list = list->next;
    }
  return NULL;
}
