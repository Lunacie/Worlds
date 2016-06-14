/*                               -*- Mode: C -*- 
 * 
 * Filename: frustrum.h
 * Description: 
 * Author: Lunacie
 * Created: Fri Nov 20 21:29:15 2015 (+0100)
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

#ifndef			FRUSTRUM_H
#define			FRUSTRUM_H


typedef enum
  {
    NEAR = 0,
    FAR,
    
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,

    _NB_PLANES
  }t_planeID;


typedef enum
  {
    TOP_LEFT = 0,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
  }t_corners;

typedef struct		s_plane
{
  char			id;
  double		width;
  double		height;

  // only free those from NEAR+FAR planes
  Vector		*corners[4];
  Vector		center;
  Vector		*normal;
  double		D;
}			t_plane;

typedef struct		s_frustrum
{
  int			fov;
  double	        ratio;
  double	        nearDist;
  double	        farDist;

  Vector		pos;
  Vector		center;
  Vector		up;

  t_plane		planes[_NB_PLANES];
}			t_frustrum;


t_frustrum		*getFrustrum(t_frustrum *tmp);
static int		computePlane(t_frustrum *frustrum, Vector *X, Vector *Y, Vector *Z, t_planeID id);
static Vector		*getPlaneNormal(t_frustrum *frustrum, t_planeID id);

bool			isInsideFrustrum(double x, double y, double z);

#endif			/* FRUSTRUM_H */
