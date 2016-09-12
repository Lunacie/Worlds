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


void			drawChunks(Map *map, float x, float y, float z)
{
  size_t		chunk;

  size_t		_x = 0;
  size_t		_y = 0;
  size_t		_z = 0;

  char			type;

  chunk = 0;
  
  for (_x = 0; _x < map->edgeSize; _x += 1)
    {
      for (_y = 0; _y < map->edgeSize; _y += 1)
	{
	  for (_z = 0; _z < map->edgeSize; _z += 1)
	    {
	      
	      /* printf("%f %f %f\n", x + (_x * PIXEL_PER_VOXEL), */
	      /* 	     y + (_y * PIXEL_PER_VOXEL), */
	      /* 	     z + (_z * PIXEL_PER_VOXEL)); */
	      
	      type = map->buffer[_x][_y][_z];
	      if (type == 0)
		type = 1;

	      if (type)
		drawCube_primitive(
		  x + (_x * PIXEL_PER_VOXEL),
		  y + (_y * PIXEL_PER_VOXEL),
		  z + (_z * PIXEL_PER_VOXEL),
		  type, false, PIXEL_PER_VOXEL);
		
	      /* printf("\n\t\t%f %f %f\n", _x, _y, _z); */
	      /* drawCube_primitive(_x, _y, _z, */
	      /* 	/\* map->buffer[_x][_y][_z] *\/7, false, PIXEL_PER_VOXEL);  */

	    }
	}
    }
  /* exit(0); */
  
}
