/*                               -*- Mode: C -*- 
 * 
 * Filename: camera.h
 * Description: 
 * Author: Lunacie
 * Created: Sat Oct 31 02:26:20 2015 (+0100)
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


#ifndef			CAMERA_H
#define			CAMERA_H

#include		"event.h"
#include		"vector.h"
#include		"frustrum.h"

void			handle_camera(Event *events);
static void		camera(Event *events);
static void		debugCamera(Event *events);


typedef struct		s_cameraData
{
  Vector		translation;
  Vector		rotation;
}			t_cameraData;

t_cameraData		*getCameraData();

#endif			/* CAMERA_H */
