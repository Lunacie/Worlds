/*                               -*- Mode: C -*- 
 * 
 * Filename: draw_camera.c
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
#include		"camera.h"

int			draw_camera(void)
{
  t_frustrum		*frustrum;
  t_cameraData		*camera;

  double		x;
  double		y;
  double		z;

  double		width;
  double		height;
  size_t		i;
  size_t		j;
  Vector		*vector;
  Vector		*tmp;

  if (!(camera = getCameraData(NULL)))
    return FAILURE;
  if (!(frustrum = getFrustrum(NULL)))
    return FAILURE;

  /* glPushMatrix(); */
  /* glTranslatef(0, 0, -camera->translation.z); */
  /* glRotated(-camera->rotation.x, 0, 1, 0); */

  glColor3ub(255, 255, 255);


  // drawing planes
  for (j = 0; j < 6; j++)
    {
      glBegin(GL_LINE_LOOP);
      for (i = 0; i < 4; i++)
	{
	  /* printf("i=%d, x:%f y:%f z:%f\n", i, frustrum->planes[NEAR].corners[i]->x, */
	  /* 		 frustrum->planes[NEAR].corners[i]->y, */
	  /* 	     frustrum->planes[NEAR].corners[i]->z); */
	  glVertex3d(frustrum->planes[j].corners[i]->x,
		     frustrum->planes[j].corners[i]->y,
		     frustrum->planes[j].corners[i]->z);
	}
      /* printf("\n"); */
      glEnd();

      /* if (1) */
      /* /\* if (j == NEAR || j == TOP || j == FAR || j == RIGHT || j == LEFT || j == BOTTOM) *\/ */
      /* 	{ */
      /* 	  glLineWidth(2.5); */
      /* 	  glColor3ub(255, 0, 0); */
      /* 	  glBegin(GL_LINES); */
      /* 	    glVertex3d(frustrum->planes[j].corners[3]->x, */
      /* 		       frustrum->planes[j].corners[3]->y, */
      /* 		       frustrum->planes[j].corners[3]->z); */

      /* 	  vector= frustrum->planes[j].normal; */
      /* 	  /\* vector = addVectors((Vector *)frustrum->planes[j].corners[3], frustrum->planes[j].normal); *\/ */
      /* 	  glVertex3d(vector->x, */
      /* 		     vector->y, */
      /* 		     vector->z); */
      /* 	  /\* free(vector); *\/ */
      
      /* 	  glEnd(); */
      /* 	  glColor3ub(255, 255, 255); */
      /* 	  glLineWidth(1); */
      /* 	} */


    }
  //  glPopMatrix();
  
  return 0;
}
