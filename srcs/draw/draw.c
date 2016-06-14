/*                               -*- Mode: C -*- 
 * 
 * Filename: draw.c
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 15:31:55 2014 (+0100)
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

size_t			rendered = 0;

int			draw()
{
  float			x = 0.1;
  float			y = 0.1;
  float			z = 0.1;
  
  rendered = 0;
  draw_camera();
  draw_map();
  /* debugOncePerSecond("Number of objects rendered : %d\n", (int)rendered); */
  /* draw_model(); */
  flushScreen();
}


