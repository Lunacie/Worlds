/*                               -*- Mode: C -*- 
 * 
 * Filename: octree.c
 * Description: 
 * Author: Lunacie
 * Created: Thu Sep  8 05:31:48 2016 (+0200)
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

#include		<string.h>

#include		"program.h"
#include		"map.h"
#include		"octree.h"

t_octreeNode		*buildOctree(Map *map, size_t level,
				     size_t minX, size_t maxX, 
				     size_t minY, size_t maxY, 
				     size_t minZ, size_t maxZ,
				     t_octreeNode *parent)
{
  t_octreeNode	*node;
  size_t	i;

  size_t medianX = minX + ((maxX - minX)/ 2);
  size_t medianY = minY + ((maxY - minY)/ 2);
  size_t medianZ = minZ + ((maxZ - minZ)/ 2);


  if (level < map->subdivisions)
    { 
      if (!(node = malloc(sizeof(t_octreeNode))))
	return NULL;
      if (!(node->children = malloc(sizeof(t_octreeNode *) * 8)))
	return NULL;
      for (i = 0; i < 8; i++)
	node->children[i] = NULL;

      node->subdivision.minX = minX;
      node->subdivision.maxX = maxX;
      node->subdivision.medianX = medianX;

      node->subdivision.minY = minY;
      node->subdivision.maxY = maxY;
      node->subdivision.medianY = medianY;

      node->subdivision.minZ = minZ;
      node->subdivision.maxZ = maxZ;
      node->subdivision.medianZ = medianZ;

      node->level = level;
      node->type = 0;

      node->parent = node->parent;

   
      /* if (level == 2) */
      /* 	{ */
      	  /* Display subdivision with colors */
      	  /* colorOctree(map, */
      	  /* 	      minX, maxX, medianX, */
      	  /* 	      minY, maxY, medianY, */
      	  /* 	      minZ, maxZ, medianZ); */
      /* 	} */
      
      if (needToSubdivise(map, node))
	{
	  // Bottom, right, front
	  node->children[0] = buildOctree(map, level + 1,
					  minX, medianX,
					  minY, medianY,
					      minZ, medianZ, node);

	  /* // Bottom, right, back */
	  node->children[1] = buildOctree(map, level + 1,
					  minX, medianX,
					  minY, medianY,
					  medianZ, maxZ, node);
	  /* // Bottom, left, front */
	  node->children[2] = buildOctree(map, level + 1,
					  medianX, maxX,
					  minY, medianY,
					  minZ, medianZ, node);
	  /* // Bottom, left, back */
	  node->children[3] = buildOctree(map, level + 1,
					  medianX, maxX,
					  minY, medianY,
					  medianZ, maxZ, node);

	  /* // Top, left, back */
	  node->children[4] = buildOctree(map, level + 1,
					  medianX, maxX,
					  medianY, maxY,
					  medianZ, maxZ, node);
	  /* // Top, right, back */
	  node->children[5] = buildOctree(map, level + 1,
					  minX, medianX,
					  medianY, maxY,
					  medianZ, maxZ, node);
	  /* // Top, right, front */
	  node->children[6] = buildOctree(map, level + 1,
					  minX, medianX,
					  medianY, maxY,
					  minZ, medianZ, node);
	  /* // Top, left, front */
	  node->children[7] = buildOctree(map, level + 1,
					  medianX, maxX,
					  medianY, maxY,
					  minZ, medianZ, node);

	  for (i = 0; i < 8; i++)
	    {
	      if (node->children[i])
		node->children[i]->childId = i;
	    }

	}
      else
	node->type = 
	  map->buffer[node->subdivision.minX][node->subdivision.minY][node->subdivision.minZ];

    }
  else
    return NULL;
  
  return node;
}



t_bool			needToSubdivise(Map *map, t_octreeNode *node)
{
  size_t		x, y, z;
  char			last;
  t_bool		start = true;

  last = 0;
  for (x = node->subdivision.minX; x < node->subdivision.maxX; x++)
    {
      for (y = node->subdivision.minY; y < node->subdivision.maxY; y++)
	{
	  for (z = node->subdivision.minZ; z < node->subdivision.maxZ; z++)
	    {
	      if (start == true)
		{
		  last = map->buffer[x][y][z];
		  start = false;
		}
	      else if (last != map->buffer[x][y][z])
		return true;
	    }
	}
    }
  node->type = last;
  return false;
}


void			printOctree(Map *map, t_octreeNode *node)
{
  size_t		i;
  size_t		count;
  
  for (i = 0; i < node->level; i++)
    printf("\t");
  printf("Level(%d) child[%d] ------------\n", node->level, node->childId);
 for (i = 0; i < node->level; i++)
	printf("\t");
      printf("type : %d - size %d", node->type,
	     node->subdivision.maxX - node->subdivision.minX);
      if (node->type != 0)
	printf(" #################################");
      printf("\n");

  count = 0;
  for (i = 0; i < 8; i++)
    {
      if (node->children[i])
	{
	  count += 1;
	  printOctree(map, node->children[i]);
	}
    }
  /* if (!count) */
  /*   { */
      /* size_t x, y, z; */
      /* for (x = node->subdivision.minX; x < node->subdivision.maxX; x++) */
      /* 	{ */
      /* 	  for (y = node->subdivision.minY; y < node->subdivision.maxY; y++) */
      /* 	    { */
      /* 	      for (z = node->subdivision.minZ; z < node->subdivision.maxZ; z++) */
      /* 		{ */
      /* 		  printf("%d ", map->buffer[x][y][z]); */
      /* 		} */
      /* 	    } */
      /* 	} */
    /* } */
  printf("\n");
}


void			colorOctree(Map *map,
				    size_t minX, size_t maxX, size_t medianX, 
				    size_t minY, size_t maxY, size_t medianY, 
				    size_t minZ, size_t maxZ, size_t medianZ)
{
  size_t x, y, z;

      /* /\* // Top Left Back *\/ */
      for (x = medianX; x < maxX; x++)
      	{
      	  for (y = medianY; y < maxY; y++)
      	    {
      	      for (z = medianZ; z < maxZ; z++)
      		{
      		  map->buffer[x][y][z] = 3;
      		}
      	    }
      	}

      // bottom Right Front
      for (x = minX; x < medianX; x++)
      	{
      	  for (y = minY; y < medianY; y++)
      	    {
      	      for (z = minZ; z < medianZ; z++)
      		{
      		  map->buffer[x][y][z] = 2;
      		}
      	    }
      	}

      /* bottom Right back */
      for (x = minX; x < medianX; x++)
      	{
      	  for (y = minY; y < medianY; y++)
      	    {
      	      for (z = medianZ; z < maxZ; z++)
      		{
      		  map->buffer[x][y][z] = 9;
      		}
      	    }
      	}

      /* bottom Left Front */
      for (x =  medianX; x <  maxX; x++)
      	{
      	  for (y = minY; y < medianY; y++)
      	    {
      	      for (z = minZ; z < medianZ; z++)
      		{
      		  map->buffer[x][y][z] = 5;
      		}
      	    }
      	}


      /* bottom Left back */
      for (x =  medianX; x <  maxX; x++)
      	{
      	  for (y = minY; y < medianY; y++)
      	    {
      	      for (z = medianZ; z < maxZ; z++)
      		{
      		  map->buffer[x][y][z] = 6;
      		}
      	    }
      	}


      /* /\* Top right Back *\/ */
      for (x = minX; x < medianX; x++)
      	{
      	  for (y = medianY; y < maxY; y++)
      	    {
      	      for (z = medianZ; z < maxZ; z++)
      		{
      		  map->buffer[x][y][z] = 4;
      		}
      	    }
      	}

      // Top right Front
      for (x = minX; x < medianX; x++)
      	{
      	  for (y = medianY; y < maxY; y++)
      	    {
      	      for (z = minZ; z < medianZ; z++)
      		{
      		  map->buffer[x][y][z] = 8;
      		}
      	    }
      	}

      // Top left Front
      for (x = medianX; x < maxX; x++)
      	{
      	  for (y = medianY; y < maxY; y++)
      	    {
      	      for (z = minZ; z < medianZ; z++)
      		{
      		  map->buffer[x][y][z] = 10;
      		}
      	    }
      	}
  
}
