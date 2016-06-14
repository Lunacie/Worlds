/*                               -*- Mode: C -*- 
 * 
 * Filename: obj_draw.c
 * Description: 
 * Author: Lunacie
 * Created: Thu Jan 29 22:30:47 2015 (+0100)
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
#include		"textureMap.h"

int			obj_draw(t_obj *obj)
{
  float			x;
  float			y;
  float			z;
  size_t		currentFace = 0;
  size_t		currentVertex = 0;
  size_t		index = 0;

  t_list		*faces;
  t_face		*face;
  size_t		i;

  t_vertex		*vertex;
  t_vertex		*texel;
  t_textureMap		diffuseMap;
  t_texture		*diffuseTexture;


  diffuseTexture = NULL;
  if (obj->materials && obj->materials->content)
    {
      diffuseMap = ((t_material *)(obj->materials->content))->textureMaps[DIFFUSE];
      if ((diffuseTexture = diffuseMap.data))
      	{
      	  glEnable(GL_TEXTURE_2D);
      	  glBindTexture(GL_TEXTURE_2D, diffuseTexture->id);
      	}

    }

  if (obj->faceType == TRIS)
    glBegin(GL_TRIANGLES);
  else if (obj->faceType == QUADS)
    glBegin(GL_QUADS);


  /* glColor3ub(255, 255, 0); //face yellow */

  faces = obj->faces;
  while (faces)
    {
      if (faces->content)
	{
	  face = (t_face *)faces->content;
	  for (i = 0; i < 3; i++)
	    {

	      // Draw Normal
	      if ((vertex = face->faceVertex[i].vn))
	      	{
	      	  x = vertex->x;
	      	  y = vertex->y;
	      	  z = vertex->z;
	      	  /* debug("| | | | | Drawing Normal x : %f -- y : %f -- z : %f\n", x, y, z); */
	      	  glNormal3f(x, y, z);
	      	}

	      // Draw Texture
	      //	-- diffuse
	      if ( diffuseTexture && (texel = face->faceVertex[i].vt))
	      	{
	      	  x = texel->x;
	      	  y = texel->y;
	      	  /* debug("| | | | | Drawing Texel x : %f -- y : %f\n", x, y); */
	      	  glTexCoord2f(x, y);
	      	}


	      /* if (diffuseTexture && texels && (texel = (t_uv *)(texels->content))) */
	      /* 	{ */
	      /* 	  x = texel->x; */
	      /* 	  y = texel->y; */
	      /* 	  glTexCoord2f(x, y); */
	      /* 	  debug("| | | | | Drawing Texel x : %f -- y : %f\n", x, y); */
	      /* 	  texels = texels->next; */
	      /* 	} */

	      // Draw Vertex
	      if ((vertex = face->faceVertex[i].v))
		{
		  x = vertex->x;
		  y = vertex->y;
		  z = vertex->z;
		  /* debug("| | | | | Drawing Vertex x : %f -- y : %f -- z : %f\n", x, y, z); */
		  glVertex3f(x, y, z);
		}
	    }
	}
      faces = faces->next;
    }

  glEnd();
  return 0;
}

