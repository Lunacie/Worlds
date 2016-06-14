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

  float			_x = 0;
  float			_y = 0;
  float			_z = 0;


  chunk = 0;
  for (_x = 0; _x < map->multiplier; _x++)
    {
      for (_z = 0; _z < map->multiplier ; _z++)
	{
	  // full chunk
	  if (chunkIsFull(map, chunk) == true)
	    {
	      
	      if (getVoxel(map, chunk, 0, 0) == 0); // full chunk air
	      else 	      // full chunk block
		{
		  drawCube_primitive(x + ((_x * PIXEL_PER_VOXEL) * map->multiplier * map->multiplier),
				     y + ((_y * PIXEL_PER_VOXEL) * map->multiplier * map->multiplier),
				     z + ((_z * PIXEL_PER_VOXEL) * map->multiplier * map->multiplier),
				     getVoxel(map, chunk, 0, 0), false, 
				     PIXEL_PER_VOXEL * map->multiplier * map->multiplier);
		}
	      
	    }
	  else
	    {
	      drawCubes(map,
			x + (((_x * PIXEL_PER_VOXEL) * map->multiplier) * map->multiplier),
			y + (((_y * PIXEL_PER_VOXEL) * map->multiplier) * map->multiplier),
			z + (((_z * PIXEL_PER_VOXEL) * map->multiplier) * map->multiplier),
			chunk);
	    }
	  chunk++;
	  
	  if (chunk >= map->nbChunks)
	    return;
	}
    }
}
