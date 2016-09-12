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
#include		"draw.h"
#include		"draw_map.h"
#include		"obj.h"
#include		"material.h"
#include		"event.h"

#include		"gameEngine.h"
#include		"map.h"
#include		"vector.h"
#include		"frustrum.h"
#include		"camera.h"
#include		"transform.h"

#include		"voxel.h"

extern size_t		rendered;
extern t_bool		displayBox;
extern e_MapDisplayMode displayMode;
extern size_t		pixelCount;

void		drawVoxels(Map *map, float x, float y, float z, size_t cube, size_t chunk)
{
  /* int		voxel; */

  /* size_t		_x = 0; */
  /* size_t		_y = 0; */
  /* size_t		_z = 0; */


  /* voxel = 0; */
  /* // X */
  /* /\* for (_x = 0; _x < map->multiplier; _x++) *\/ */
  /* for (_x = 0; _x < 4; _x++) */
  /*   { */
  /*     /\* printf("--- x\n"); *\/ */
  /*     // Y */
  /*     /\* for (_y = 0; _y < map->multiplier; _y++) *\/ */
  /*     for (_y = 0; _y < 4; _y++) */
  /* 	{ */
  /* 	  /\* printf("\t--- y\n"); *\/ */
  /* 	  // Z */
  /* 	  /\* for (_z = 0; _z < map->multiplier ; _z++) *\/ */
  /* 	  for (_z = 0; _z < 4 ; _z++) */
  /* 	    { */
  /* 	      /\* printf("\t\t--- z\n"); *\/ */
  /* 	      /\* debugOncePerSecond("x : %f", x + (_x * PIXEL_PER_VOXEL)); *\/ */
  /* 	      if (getVoxel(map, chunk, cube, voxel) != 0) */
  /* 		{ */
  /* 		  drawCube_primitive(x + (_x * PIXEL_PER_VOXEL), */
  /* 				     y + (_y * PIXEL_PER_VOXEL), */
  /* 				     z + (_z * PIXEL_PER_VOXEL), */
  /* 				     getVoxel(map, chunk, cube, voxel), */
  /* 				     false, PIXEL_PER_VOXEL); */
  /* 		} */
  /* 	      /\* printf("\t\tdrew voxel %d\n", voxel); *\/ */
  /* 	      voxel++; */
  /* 	      if (voxel >= map->nbVoxelsPerCubes) */
  /* 		return; */
  /* 	    } */
  /* 	} */
  /*   } */
}

