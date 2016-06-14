/*                               -*- Mode: C -*- 
 * 
 * Filename: draw_primitives.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Nov 21 18:13:39 2015 (+0100)
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


#include		"program.h"

#include		"graphicEngine.h"
#include		"draw.h"
#include		"vector.h"


void			drawRectangle(Vector *p1, Vector *p2, Vector *p3, Vector *p4, GLuint poly)
{
  glBegin(poly);
  glVertex3d(p1->x, p1->y, p1->z);
  glVertex3d(p2->x, p2->y, p2->z);
  glVertex3d(p3->x, p3->y, p3->z);
  glVertex3d(p4->x, p4->y, p4->z);
  glEnd();
}
