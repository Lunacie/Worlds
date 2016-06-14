/*                               -*- Mode: C -*- 
 * 
 * Filename: voxel.h
 * Description: 
 * Author: Lunacie
 * Created: Wed Apr 30 03:42:05 2014 (+0200)
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

#ifndef			VOXEL_H
#define			VOXEL_H

enum
  {
    VOXEL_TOP_TOP_LEFT,
    VOXEL_TOP_TOP_RIGHT,
    VOXEL_TOP_BOTTOM_RIGHT,
    VOXEL_TOP_BOTTOM_LEFT,

    VOXEL_BOTTOM_TOP_LEFT,
    VOXEL_BOTTOM_TOP_RIGHT,
    VOXEL_BOTTOM_BOTTOM_RIGHT,
    VOXEL_BOTTOM_BOTTOM_LEFT,

    _NB_VOXEL_CORNERS
  };


#endif			/* VOXEL_H */
