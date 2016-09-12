/*                               -*- Mode: C -*- 
 * 
 * Filename: octree.c
 * Description: 
 * Author: Lunacie
 * Created: Fri Sep  9 05:12:03 2016 (+0200)
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
#include		"octree.h"

extern size_t		rendered;
extern t_bool		displayBox;
extern e_MapDisplayMode displayMode;
extern size_t		pixelCount;


void			drawOctree(Map *map, float x, float y, float z, t_octreeNode *node)
{
  size_t		i;
  size_t		count;
  char			type;
  
  /* printf("draw at : %f %f %f\n", */
  /*   /\* x +  *\/node->subdivision.minX, */
  /*   /\* y + *\/ node->subdivision.minY, */
  /* 	 /\* z +  *\/node->subdivision.minZ); */
  /* printf("size : (%d - %d) * %f = %f (%f)\n\n", */
  /* 	 node->subdivision.maxX , node->subdivision.minX,  PIXEL_PER_VOXEL, */
  /* 	 (node->subdivision.maxX - node->subdivision.minX) * PIXEL_PER_VOXEL, */
  /* 	 ((node->subdivision.maxX - node->subdivision.minX) * PIXEL_PER_VOXEL) * -1); */

  type = node->type;

  if (type == 0)
    type = 1;

  drawCube_primitive(
    (x + node->subdivision.maxX * PIXEL_PER_VOXEL) - PIXEL_PER_VOXEL,
    (y + node->subdivision.maxY * PIXEL_PER_VOXEL) - PIXEL_PER_VOXEL,
    (z + node->subdivision.maxZ * PIXEL_PER_VOXEL) - PIXEL_PER_VOXEL,
    type, 
    false, ((node->subdivision.maxX - node->subdivision.minX) * PIXEL_PER_VOXEL));


  count = 0;
  for (i = 0; i < 8; i++)
    {
      if (node->children[i])
	{
	  count += 1;
	  drawOctree(map, x, y, z, node->children[i]);
	}
    }
}
