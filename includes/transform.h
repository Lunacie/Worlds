/*                               -*- Mode: C -*- 
 * 
 * Filename: transform.h
 * Description: 
 * Author: Lunacie
 * Created: Sat Nov 21 16:29:08 2015 (+0100)
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


#ifndef			TRANSFORM3D_H
#define			TRANSFORM3D_H

#include		"vector.h"

typedef enum
  {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
  }			t_axis;

Vector			*applyRotation(t_axis axis, double x, double y, double z, double value);
Vector			*applyRotationAboutPoint(t_axis axis, double x, double y, double z, double value);
void			applyTranslation(Vector *vector, double x, double y, double z);

#endif			/* TRANSFORM3D_H */
