/*                               -*- Mode: C -*- 
 * 
 * Filename: camera.c
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 17:05:29 2014 (+0100)
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

#include		<math.h>

#include		"debugHandling.h"
#include		"graphicEngine.h"
#include		"camera.h"
#include		"event.h"
#include		"vector.h"
#include		"frustrum.h"

int		fov = 65;
double	        ratio = (double)16/9;

double	        nearDist = 0.1;
double	        farDist = 30;


void			handle_camera(Event *events)
{
  static int		horizontal = 0;
  static int		vertical = 0;
  static int		distance = 3;
  static t_bool		debugCameraON = true;

  gluPerspective(fov, ratio, nearDist, farDist);

  if (events->key_d && debugCameraON == true)
    {
      debugCameraON = false;
      debug("Debug Camera OFF");
    }
  else if (events->key_d && debugCameraON == false)
    {
      debugCameraON = true;
      debug("Debug Camera ON");
    }

  if (debugCameraON == false)
    camera(events);
  else if (debugCameraON == true)
    debugCamera(events);
}


t_cameraData		*getCameraData(Event *events)
{
  static t_cameraData   *data = NULL;

  if (data == NULL)
    {
      if (!(data = malloc(sizeof(t_cameraData))))
	return NULL;
      data->translation.x = 0;
      data->translation.y = 0;
      data->translation.z = 0;
      data->rotation.x = 0;
      data->rotation.y = 0;
      data->rotation.z = 0;
    }
  if (events)
    {
      /* if (events->left) */
      /* 	data->translation.x -= 0.1; */
      /* if (events->right) */
      /* 	data->translation.x += 0.1; */
      if (events->key_s == false)
	{
	  if (events->left)
	    data->rotation.x -= 0.1;
	  if (events->right)
	    data->rotation.x += 0.1;
	  if (events->up)
	    data->translation.z -= 0.1;
	  if (events->down)
	    data->translation.z += 0.1;
	}
    }
  return data;
}

static void		camera(Event *events)
{
  t_frustrum		*frustrum;
  t_cameraData		*data;
  
  if (!(data = getCameraData(events)))
    return;
  if (!(frustrum = getFrustrum(NULL)))
    return;

  
  gluLookAt(
    frustrum->pos.x, frustrum->pos.y, frustrum->pos.z,
    frustrum->center.x, frustrum->center.y, frustrum->center.z,
    0, 1, 0);
  
}


static void		debugCamera(Event *events)
{
  static double		posX = 3;
  static double		posY = 7;
  static double		posZ = 3;

  static double		centerX = 0;
  static double		centerY = 0;
  static double		centerZ = 0;

  static int		horizontal = 0;
  static int		vertical = 0;
  static int		distance = 3;
  static t_bool		debugCamera = true;
  
  
  if (events->left)
    horizontal -= 1;
  if (events->right)
    horizontal += 1;
  if (events->up)
    distance += 1;
  if (events->down)
    distance -= 1;
  
  gluLookAt(
    posX, posY, posZ,
    centerX, centerY, centerZ,
    0, 1, 0);
  
  
  glRotated(horizontal, 0, 1, 0);
   glTranslatef(horizontal, vertical, distance);
}

