/*                               -*- Mode: C -*- 
 * 
 * Filename: frustrum.c
 * Description: 
 * Author: Lunacie
 * Created: Fri Nov 20 21:31:56 2015 (+0100)
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

extern int		fov;
extern double	        ratio;

extern double	        nearDist;
extern double	        farDist;

t_frustrum		*getFrustrum(t_frustrum *tmp)
{
  static t_frustrum	*frustrum = NULL;
  Vector		*Z;
  Vector		*X;
  Vector		*Y;
  Vector		*ret, *ret2, *ret3;
  

  if (!frustrum && !tmp)
    {
      if (!(frustrum = malloc(sizeof(t_frustrum))))
	return NULL;

      frustrum->fov = fov;
      frustrum->ratio = ratio;
      frustrum->nearDist = nearDist;
      frustrum->farDist = farDist;
	
      frustrum->pos.x = 0;
      frustrum->pos.y = 0;
      frustrum->pos.z = -1;
      frustrum->center.x = 0;
      frustrum->center.y = 0;
      frustrum->center.z = nearDist;
      frustrum->up.x = 0;
      frustrum->up.y = 1;
      frustrum->up.z = 0;

      // Z axis of camera => Opposite of looking direction
      Z = substractVectors(&frustrum->pos, &frustrum->center);
      normalizeVector(Z);
	
      // X axis of the camera
      X = crossProductVectors(&frustrum->up, Z);
      normalizeVector(X);

      // REAL up Vector
      Y = crossProductVectors(Z, X);


      // Centers for near and far planes => 
      //	nearCenter = p - Z * nearD;
      ret = multiplyVectorByValue(Z, frustrum->nearDist);
      substractVectorsResult((Vector *)&frustrum->pos,
			     ret,
			     (Vector *)&frustrum->planes[NEAR].center);
      free(ret);
      //	farCenter = p - Z * farD;
      ret = multiplyVectorByValue(Z, frustrum->farDist);
      substractVectorsResult((Vector *)&frustrum->pos,
			     ret,
			     (Vector *)&frustrum->planes[FAR].center);


      frustrum->planes[NEAR].height = 2 * tan(fov / 2) * nearDist;
      frustrum->planes[NEAR].width = frustrum->planes[NEAR].height * ratio;
      frustrum->planes[FAR].height = 2 * tan(fov / 2) * farDist;
      frustrum->planes[FAR].width = frustrum->planes[FAR].height * ratio;

      // compute the 4 corners of the frustum on the near and far planes
      computePlane(frustrum, X, Y, Z, NEAR);
      computePlane(frustrum, X, Y, Z, FAR);

      computePlane(frustrum, X, Y, Z, TOP);
      computePlane(frustrum, X, Y, Z, BOTTOM);
      computePlane(frustrum, X, Y, Z, LEFT);
      computePlane(frustrum, X, Y, Z, RIGHT);
      


	}
	if (tmp)
	  frustrum = tmp;
      return frustrum;
    }

  static int		computePlane(t_frustrum *frustrum, Vector *X, Vector *Y, Vector *Z, t_planeID id)
  {
    Vector		*ret;
    Vector		*ret2;
    Vector		*ret3;

    if (id == NEAR || id == FAR)
      {
	/* ntl = nc + (Y * nh) - (X * nw); */
	ret = multiplyVectorByValue(Y, frustrum->planes[id].height);
	ret2 = multiplyVectorByValue(X, frustrum->planes[id].width);
	ret3 = addVectors((Vector *)&frustrum->planes[id].center, ret);
	frustrum->planes[id].corners[TOP_LEFT] = (Vector *)substractVectors(ret3, ret2);
	free(ret);
	free(ret2);
	free(ret3);
	/* ntr = nc + Y * nh + X * nw; */
	ret = multiplyVectorByValue(Y, frustrum->planes[id].height);
	ret2 = multiplyVectorByValue(X, frustrum->planes[id].width);
	ret3 = addVectors((Vector *)&frustrum->planes[id].center, ret);
	frustrum->planes[id].corners[TOP_RIGHT] = (Vector *)addVectors(ret3, ret2);
	free(ret);
	free(ret2);
	free(ret3);
	/* nbr = nc - Y * nh + X * nw; */
	ret = multiplyVectorByValue(Y, frustrum->planes[id].height);
	ret2 = multiplyVectorByValue(X, frustrum->planes[id].width);
	ret3 = substractVectors((Vector *)&frustrum->planes[id].center, ret);
	frustrum->planes[id].corners[BOTTOM_RIGHT] = (Vector *)addVectors(ret3, ret2);
	free(ret);
	free(ret2);
	free(ret3);
	/* nbl = nc - Y * nh - X * nw; */
	ret = multiplyVectorByValue(Y, frustrum->planes[id].height);
	ret2 = multiplyVectorByValue(X, frustrum->planes[id].width);
	ret3 = substractVectors((Vector *)&frustrum->planes[id].center, ret);
	frustrum->planes[id].corners[BOTTOM_LEFT] = (Vector *)substractVectors(ret3, ret2);
	free(ret);
	free(ret2);
	free(ret3);
      }
    
    else if (id == TOP)
      {
	frustrum->planes[id].corners[TOP_LEFT] = frustrum->planes[FAR].corners[TOP_LEFT];
	frustrum->planes[id].corners[TOP_RIGHT] = frustrum->planes[FAR].corners[TOP_RIGHT];
	frustrum->planes[id].corners[BOTTOM_LEFT] = frustrum->planes[NEAR].corners[TOP_LEFT];
	frustrum->planes[id].corners[BOTTOM_RIGHT] = frustrum->planes[NEAR].corners[TOP_RIGHT];
      }
    else if (id == BOTTOM)
      {
	frustrum->planes[id].corners[TOP_LEFT] = frustrum->planes[FAR].corners[BOTTOM_LEFT];
	frustrum->planes[id].corners[TOP_RIGHT] = frustrum->planes[FAR].corners[BOTTOM_RIGHT];
	frustrum->planes[id].corners[BOTTOM_LEFT] = frustrum->planes[NEAR].corners[BOTTOM_LEFT];
	frustrum->planes[id].corners[BOTTOM_RIGHT] = frustrum->planes[NEAR].corners[BOTTOM_RIGHT];
      }
    else if (id == LEFT)
      {
	frustrum->planes[id].corners[TOP_LEFT] = frustrum->planes[FAR].corners[TOP_LEFT];
	frustrum->planes[id].corners[TOP_RIGHT] = frustrum->planes[FAR].corners[BOTTOM_LEFT];
	frustrum->planes[id].corners[BOTTOM_RIGHT] = frustrum->planes[NEAR].corners[BOTTOM_LEFT];
	frustrum->planes[id].corners[BOTTOM_LEFT] = frustrum->planes[NEAR].corners[TOP_LEFT];
      }
    else if (id == RIGHT)
      {
	frustrum->planes[id].corners[TOP_LEFT] = frustrum->planes[FAR].corners[TOP_RIGHT];
	frustrum->planes[id].corners[TOP_RIGHT] = frustrum->planes[FAR].corners[BOTTOM_RIGHT];
	frustrum->planes[id].corners[BOTTOM_RIGHT] = frustrum->planes[NEAR].corners[BOTTOM_RIGHT];
	frustrum->planes[id].corners[BOTTOM_LEFT] = frustrum->planes[NEAR].corners[TOP_RIGHT];
      }

    frustrum->planes[id].normal = getPlaneNormal(frustrum, id);

    /* printf("normal : \n"); */
    /* dumpVector(*frustrum->planes[id].normal); */
    /* printf("center : \n"); */
    /* dumpVector(*(Vector*)&frustrum->planes[id].center); */
    /* printf("corners : \n"); */
    /* dumpVector(*frustrum->planes[id].corners[TOP_LEFT]); */
    /* dumpVector(*frustrum->planes[id].corners[TOP_RIGHT]); */
    /* dumpVector(*frustrum->planes[id].corners[BOTTOM_RIGHT]); */
    /* dumpVector(*frustrum->planes[id].corners[BOTTOM_LEFT]); */
    /* printf("\n"); */
    /* exit(0); */


    return 0;
  }


static Vector		*getPlaneNormal(t_frustrum *frustrum, t_planeID id)
{
  Vector		*p0, *p1, *p2;
  Vector		*u, *v, *normal;
 
  // Need 3 points to compute 2 vectors form the plane, u and v
  p0 = (Vector *)frustrum->planes[id].corners[TOP_LEFT];
  p1 = (Vector *)frustrum->planes[id].corners[TOP_RIGHT];
  p2 = (Vector *)frustrum->planes[id].corners[BOTTOM_LEFT];

  u = substractVectors(p2, p0);
  v = substractVectors(p1, p0);

  normal = crossProductVectors(u, v);
  free(u);
  free(v);
  normalizeVector(normal);
  if (id == NEAR)
      normal->z *= -1;
  if (id == TOP)
    {
      normal->y *= -1;
      normal->z *= -1;
      /* printf("TOP NORMAL : ======================\n"); */
    }
  if (id == RIGHT)
    {
      normal->z *= -1;
      normal->x *= -1;
      /* printf("TOP RIGHT : ======================\n"); */
    }
  if (id == FAR)
    {
      /* normal->z *= -1; */
      /* normal->x *= -1; */
      /* normal->y *= -1; */
    }
 
  frustrum->planes[id].D = dotProductVectors(normal, p1);
  frustrum->planes[id].D *= -1.0;
  return normal;
}

t_bool			isInsideFrustrum(double x, double y, double z)
{
  Vector		*vector;
  t_frustrum		*frustrum;
  double		dist;
  size_t		i;
  Vector		*normal;
  double		D;

  double		margin;
  size_t		count;

  margin = 0.1;
  count = 0;

  if (!(vector = malloc(sizeof(Vector))))
    exit(FAILURE);
  vector->x = x;
  vector->y = y;
  vector->z = z;
  //  dumpVector(*vector);
  if (!(frustrum = getFrustrum(NULL)))
    exit(FAILURE);
  for (i = 0; i < _NB_PLANES; i++)
    {
      normal = frustrum->planes[i].normal;
      D = frustrum->planes[i].D;
      
      dist = dotProductVectors(normal, vector) + D + margin;
      /* if (dist < 0) */
      /* 	printf("%f FALSE\n", dist); */
      /* else */
      /* 	printf("%f TRUE\n", dist); */
      if (dist < 0)
	{ 
	  count += 1;
	  free(vector);
	  return false;
	}
    }
  free(vector);

  /* if (count == _NB_PLANES - 1) */
  /*   return false; */
  
  return true;
}


