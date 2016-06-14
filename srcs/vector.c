/*                               -*- Mode: C -*- 
 * 
 * Filename: vector.c
 * Description: 
 * Author: Lunacie
 * Created: Thu Nov 19 23:01:08 2015 (+0100)
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
#include		"vector.h"

double			getVectorLength(Vector *vector)
{
  double		x;
  double		y;
  double		z;

  x = vector->x * vector->x;
  y = vector->z * vector->z;
  z = vector->z * vector->z;
  return sqrt(x + y + z);
}

Vector			*normalizeVector(Vector *vector)
{
  double		lenght;

  lenght = getVectorLength(vector);
  /* if (lenght != 0) */
  /*   { */
      /* if (vector->x != 0) */
	vector->x = vector->x / lenght;
      /* if (vector->y != 0) */
	vector->y = vector->y / lenght;
      /* if (vector->z != 0) */
	vector->z = vector->z / lenght;	
    /* } */
  return vector;
}


Vector			*substractVectors(Vector *v1, Vector *v2)
{
  Vector		*new;

  if (!(new = malloc(sizeof(Vector))))
    return NULL;
  new->x = v1->x - v2->x;
  new->y = v1->y - v2->y;
  new->z = v1->z - v2->z;
  return new;
}


Vector			substractVectorsResult(Vector *v1, Vector *v2, Vector *result)
{
  result->x = v1->x - v2->x;
  result->y = v1->y - v2->y;
  result->z = v1->z - v2->z;
  return *result;
}

Vector			*multiplyVectors(Vector *v1, Vector *v2)
{
  Vector		*new;

  if (!(new = malloc(sizeof(Vector))))
    return NULL;
  new->x = v1->x * v2->x;
  new->y = v1->y * v2->y;
  new->z = v1->z * v2->z;
  return new;
}


Vector			*crossProductVectors(Vector *v1, Vector *v2)
{
  Vector		*new;

  if (!(new = malloc(sizeof(Vector))))
    return NULL;
  new->x = (v1->y * v2->z) - (v1->z * v2->y);
  new->y = (v1->z * v2->x) - (v1->x * v2->z);
  new->z = (v1->x * v2->y) - (v1->y * v2->x);
  return new;
}


double			dotProductVectors(Vector *v1, Vector *v2)
{
  return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

Vector			*addVectors(Vector *v1, Vector *v2)
{
  Vector		*new;

  if (!(new = malloc(sizeof(Vector))))
    return NULL;
  new->x = v1->x + v2->x;
  new->y = v1->y + v2->y;
  new->z = v1->z + v2->z;
  return new;
}

Vector			*multiplyVectorByValue(Vector *v1, double value)
{
  Vector		*new;

  if (!(new = malloc(sizeof(Vector))))
    return NULL;
  new->x = v1->x * value;
  new->y = v1->y * value;
  new->z = v1->z * value;
  return new;
}

Vector			multiplyVectorsResult(Vector *v1, Vector *v2, Vector *result)
{
  result->x = v1->x * v2->x;
  result->y = v1->y * v2->y;
  result->z = v1->z * v2->z;
  return *result;
}

Vector			*newVector(double x, double y, double z)
{
  Vector		*vector;

  if (!(vector = malloc(sizeof(Vector))))
    exit(FAILURE);
  vector->x = x;
  vector->y = y;
  vector->z = z;
  return vector;
}

void			dumpVector(Vector vector)
{
  printf("%f %f %f\n", vector.x, vector.y, vector.z);
}
