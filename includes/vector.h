/*                               -*- Mode: C -*- 
 * 
 * Filename: vector.h
 * Description: 
 * Author: Lunacie
 * Created: Thu Nov 19 17:54:18 2015 (+0100)
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


#ifndef			VECTOR_H
#define			VECTOR_H

typedef struct		s_vector
{
  double		x;
  double		y;
  double		z;
}			Vector;


Vector			*normalizeVector(Vector *vector);
double			getVectorLength(Vector *vector);
Vector			*substractVectors(Vector *v1, Vector *v2);
Vector			*multiplyVectors(Vector *v1, Vector *v2);
Vector			*crossProductVectors(Vector *v1, Vector *v2);
double			dotProductVectors(Vector *v1, Vector *v2);
Vector			*addVectors(Vector *v1, Vector *v2);
Vector			*newVector(double x, double y, double z);
Vector			*multiplyVectorByValue(Vector *v1, double value);
Vector			substractVectorsResult(Vector *v1, Vector *v2, Vector *result);
Vector			multiplyVectorsResult(Vector *v1, Vector *v2, Vector *result);
void			dumpVector(Vector vector);

#endif			/* VECTOR_H */
