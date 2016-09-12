/*                               -*- Mode: C -*- 
 * 
 * Filename: octree.h
 * Description: 
 * Author: Lunacie
 * Created: Thu Sep  8 05:30:22 2016 (+0200)
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


#ifndef			OCTREE_H
#define			OCTREE_H

#include		"map.h"

typedef struct		s_subdivision
{
  size_t		minX;
  size_t		maxX;
  size_t		medianX;

  size_t		minY;
  size_t		maxY;
  size_t		medianY;

  size_t		minZ;
  size_t		maxZ;
  size_t		medianZ;
}			t_subdivision;


typedef struct		s_octreeNode
{
  size_t		level;
  struct s_octreeNode	**children;
  struct s_octreeNode	*parent;
  size_t		childId;
  t_subdivision		subdivision;
  char			type;
}			t_octreeNode;


t_octreeNode		*buildOctree(Map *map, size_t level,
			size_t minX, size_t maxX, 
			size_t minY, size_t maxY, 
			size_t minZ, size_t maxZ,
			t_octreeNode *parent);

void			colorOctree(Map *map,
				    size_t minX, size_t maxX, size_t medianX, 
				    size_t minY, size_t maxY, size_t medianY, 
				    size_t minZ, size_t maxZ, size_t medianZ);


t_bool			needToSubdivise(Map *map, t_octreeNode *node);

void			printOctree(Map *map, t_octreeNode *node);

#endif			/* OCTREE_H */
