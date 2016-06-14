/*                               -*- Mode: C -*- 
 * 
 * Filename: draw_background.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Jan 24 17:43:25 2015 (+0100)
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
#include		"material.h"

int			draw_background(void)
{
  /* static t_obj		*obj = NULL; */
  static t_material		*material = NULL;

  /* if (!obj) */
  /*   { */
  /*     /\* if (obj = getObj("CitadelIsland",NULL,  TRIS)) *\/ */
  /*     /\* if (obj = getObj("tris",NULL,  TRIS)) *\/ */
  /*     /\* if (obj = getObj("cat", "cat/", TRIS)) *\/ */
  /*     if (obj = getObj("chunk00_00", NULL,  TRIS)) */
  /*     /\* if (obj = getObj("single_quad", NULL,  QUADS)) *\/ */
  /* 	{ */
  /* 	  debug("| | | | Background object retrived"); */

  /* 	  /\* if ( obj->materialName && (material = getMaterial(obj->materialName, "cat/"))) *\/ */
  /* 	  /\*   obj->materials = addToList(NULL, material); *\/ */
  /* 	  /\* else if (!obj->materialName) *\/ */
  /* 	  /\*   debug("| | | | | No material to load for background"); *\/ */
  /* 	  /\* else *\/ */
  /* 	  /\*   debug("| | | | | Could not load background material /!\\"); *\/ */

  /* 	} */
  /*   } */
  /* if (obj) */
  /*   obj_draw(obj); */
  /* else */
  /*   debug("| | | | Careful, Background is missing /!\\"); */


   glEnable(GL_TEXTURE_2D);


  if (!material)
    material = getMaterial("cat.mtl", "cat/");
  glBindTexture(GL_TEXTURE_2D, material->textureMaps[DIFFUSE].data->id);

  /* printf("Material id : %d\n", material->textureMaps[DIFFUSE].data->id); */
  /* exit(0); */

  glBegin(GL_QUADS);

  /* glColor3ub(255,0,0); //face rouge */

  glTexCoord2f(0.0f, 0.0f);
  glVertex2d(0, 0);

  glTexCoord2f(0.0f, 1.0f);
  glVertex2d(0, 1);

  glTexCoord2f(1.0f, 1.0f);
  glVertex2d(1, 1);

  glTexCoord2f(1.0f, 0.0f);
  glVertex2d(1 ,0);
  glEnd();

  
 return 0;
}
