/*                               -*- Mode: C -*- 
 * 
 * Filename: transform.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Nov 21 16:28:50 2015 (+0100)
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

#include		"program.h"

#include		"transform.h"
#include		"vector.h"
#include		"frustrum.h"
#include		"camera.h"

Vector			*applyRotation(t_axis axis, double x, double y, double z, double value)
{
  Vector		*vector;

  vector = newVector(0, 0, 0);

  if (axis == X_AXIS)
    {
      vector->y = y * cos(value) - z * sin(value);
      vector->z = y * sin(value) + z * cos(value);
      vector->x = x;
    }
  else if (axis == Y_AXIS)
    {
      vector->z = z * cos(value) - x * sin(value);
      vector->x = z * sin(value) + x * cos(value);
      vector->y = y;
    }
  else if (axis == Z_AXIS)
    {
      vector->x = x * cos(value) - y * sin(value);
      vector->y = x * sin(value) + y * cos(value);
      vector->z = z;
    }
  return vector;
}

Vector			*applyRotationAboutPoint(t_axis axis, double x, double y, double z, double value)
{
  Vector		*origin;
  Vector		*rotated;

  origin = newVector(x, y, z);
  applyTranslation(origin, 0, 0, -1);

  rotated = applyRotation(axis, origin->x, origin->y, origin->z, value);
  
  applyTranslation(rotated, 0, 0, 1);

  free(origin);
  
  return rotated;
}


void			applyTranslation(Vector *vector, double x, double y, double z)
{
  vector->x += x;
  vector->y += y;
  vector->z += z;
}
