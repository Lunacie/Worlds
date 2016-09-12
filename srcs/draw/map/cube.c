/*                               -*- Mode: C -*- 
 * 
 * Filename: draw_map.c
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
#include		"draw_map.h"
#include		"obj.h"
#include		"material.h"
#include		"event.h"

#include		"gameEngine.h"
#include		"map.h"



extern size_t		rendered;
extern t_bool		displayBox;
extern e_MapDisplayMode displayMode;
extern size_t		pixelCount;


void		drawCubes(Map *map, float x, float y, float z, size_t chunk)
{
  size_t		cube;

  float			_x = 0;
  float			_y = 0;
  float			_z = 0;

  cube = 0;

  drawCube_primitive(x, y, z, );

}

