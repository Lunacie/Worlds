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
#include		"camera.h"

#include		"gameEngine.h"
#include		"map.h"



extern size_t		rendered;

t_bool		displayBox = false;
e_MapDisplayMode displayMode = VOXEL_MODE;
size_t		pixelCount = 0;

char			*displayModeNames[_NB_MAP_DISPLAY_MODE] = 
  {
    "Voxel", 
    "Cube", 
    "Chunk"
  };

int			draw_map(void)
{
  t_gameData		*gameData;
  Map			*map;

  size_t		chunk;
  size_t		cube;
  size_t		voxel;

  float			x = 0;
  float			y = 0;
  float			z = 0;

  Event			*events;

  if ((events = storeEvent(NULL, false)))
    {
      if (events->key_b && displayBox == true)
	{
	  displayBox = false;
	  debug("bounding box mode off");
	}
      else if (events->key_b && displayBox == false)
	{
	  displayBox = true;
	  debug("bounding box mode on");
	}

      
      if (events->key_m)
	{
	  displayMode += 1;
	  if (displayMode == _NB_MAP_DISPLAY_MODE)
	    displayMode = 0;
	  debug("%s display mode enabled.", displayModeNames[displayMode]);
	}
    }

  pixelCount = 0;
  rendered = 0;
 

  if ((gameData = handleGameData(NULL)) &&
      (map = gameData->map))
    {
      /* debug(" "); */
      /* debug("| | | | Map was succesully loaded from Game Engine. Drawing Starts : "); */


      /* glPushMatrix(); */
      /* glRotated(camera->rotation.x, 0, 1, 0); */
      /* glTranslatef(0, 0, camera->translation.z); */
      drawChunks(map, x, y, z);
      /* glPopMatrix(); */
      
    }
  else
    debug("| | | | Could not load map from game Engine");
  return 0;
}


