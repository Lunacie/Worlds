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
  // x
  for (_x = 0; _x < map->multiplier; _x++)
    {
	  // Y
	  for (_y = 0; _y < map->multiplier; _y++)
	    {
		  // Z
	      for (_z = 0; _z < map->multiplier ; _z++)
		    {
		      // full Cube
		      if (cubeIsFull(map, chunk, cube) == true)
			{
			  // full air cube
			  if (getVoxel(map, chunk, cube, 0) == 0);
			  // full cube is block
			  else
			    {
			    drawCube_primitive(x + ((_x * PIXEL_PER_VOXEL)),
					       y + ((_y * PIXEL_PER_VOXEL)),
					       z + ((_z * PIXEL_PER_VOXEL)),
					       getVoxel(map, chunk, cube, 0), false, 
					       PIXEL_PER_VOXEL * map->multiplier);
			    }
			}
		      // cube not full, draw voxels
		      else
			{
			  drawVoxels(map,
				     x + ((_x * PIXEL_PER_VOXEL) * map->multiplier),
				     y + ((_y * PIXEL_PER_VOXEL) * map->multiplier),
				     z + ((_z * PIXEL_PER_VOXEL) * map->multiplier),
				     cube, chunk);
			}
		      cube += 1;
		      if (cube >= map->nbCubesPerChunks)
			return;
		    }
	    }
    }
}

