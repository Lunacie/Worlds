/*                               -*- Mode: C -*- 
 * 
 * Filename: draw.h
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 18:16:11 2014 (+0100)
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

#ifndef			DRAW_H
#define			DRAW_H

#include		"graphicEngine.h"

#include		"draw/draw_map.h"
#include		"vector.h"

void			drawCube(float, float, float);
int			draw_model(void);
int			draw_camera(void);
void			drawRectangle(Vector *p1, Vector *p2, Vector *p3, Vector *p4, GLuint poly);
void			drawCube_primitive(float x, float y, float z, char type, t_bool boxCheck, double sizeInUnit);


#endif			/* DRAW_H */
