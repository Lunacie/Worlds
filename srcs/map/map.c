/*                               -*- Mode: C -*- 
 * 
 * Filename: map.c
 * Description: 
 * Author: Lunacie
 * Created: Wed Apr 30 03:46:22 2014 (+0200)
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

Map			*initMap(void)
{
  Map			*map;

  size_t		i, j, k;

  debug("Loading map :");
  
  if (!(map = malloc(sizeof(Map))))
    return NULL;


  /* map->nbChunks = 1; */
  /* map->nbCubesPerChunks = 1 ; */
  /* map->nbVoxelsPerCubes = 1; */
  /* map->multiplier = MULTIPLIER; */

  /* map->size = (((map->nbVoxelsPerCubes) * map->nbCubesPerChunks) * map->nbChunks); */
  /* if (!(map->buffer = malloc(map->size))) */
  /*   return NULL; */



  map->nbChunks = 1;
  map->nbCubesPerChunks = SIZE;
  map->nbVoxelsPerCubes = SIZE;
  map->multiplier = MULTIPLIER;

  map->size = (((map->nbVoxelsPerCubes) * map->nbCubesPerChunks) * map->nbChunks);
  printf("map size : %d\n", map->size);
  if (!(map->buffer = malloc(map->nbChunks * sizeof(map->buffer))))
    return NULL;
  for (i = 0; i < map->nbChunks; i++)
    {
      if (!(map->buffer[i] = malloc(map->nbCubesPerChunks * sizeof(*map->buffer))))
	return NULL;
      for (j = 0; j < map->nbCubesPerChunks; j++)
	{ 
	  if (!(map->buffer[i][j] = malloc(map->nbVoxelsPerCubes * sizeof(**map->buffer))))
	    return NULL;
	  for (k = 0; k < map->nbVoxelsPerCubes; k++)
	    map->buffer[i][j][k] = 0;
	}
    }

  // TestMap
  
  
  for (k = 0; k < map->nbVoxelsPerCubes; k++)
    setVoxel(map, 0, 0, k, 1);
  setVoxel(map, 0, 1, 0, 1);
  for (k = 0; k < map->nbVoxelsPerCubes - 1; k++)
    setVoxel(map, 0, 1, k, 1);
  printMap(map);
  return map;
}




void			setVoxel(Map *map, size_t chunk, size_t cube, size_t voxel, char type)
{
  map->buffer[chunk][cube][voxel] = type;
}

char			getVoxel(Map *map, size_t chunk, size_t cube, size_t voxel)
{
  return map->buffer[chunk][cube][voxel];
}



bool		chunkIsFull(Map *map, size_t chunk)

{
  size_t	i;

  for (i = 0; i < map->nbCubesPerChunks; i++)
    {
      if (cubeIsFull(map, chunk, i) == false)
	return false;
    }
  if (i >= map->nbCubesPerChunks)
    return true;
  return false;
}



bool		cubeIsFull(Map *map, size_t chunk, size_t cube)

{
  char		voxel;
  size_t	i;

  voxel = getVoxel(map, chunk, cube, 0);
  for (i = 0; i < map->nbVoxelsPerCubes; i++)
    {
      if (getVoxel(map, chunk, cube, i) != voxel)
	return false;
    }
  if (i >= map->nbVoxelsPerCubes)
    return true;
  return false;
}





void			printMap(Map *map)
{
  size_t		i;
  size_t		j;
  size_t		k;
  size_t		count;

  count = 0;
  printf("\t----------------------------------------------------------------\n");
  for (i = 0; i < map->nbChunks; i++)
    {
      printf("\tCHUNK #%d\n", i);
      for (j = 0; j < map->nbCubesPerChunks; j++)
  	{
	  printf("%d\t",j);
	  for (k = 0; k < map->nbVoxelsPerCubes; k++)
	    {
	      printf("%c", getVoxel(map, i, j, k) + '0'); 
	      count++;
	    }
	  printf("\n");
	}
    }
  printf("Count : %d\n", count);
  printf("\t----------------------------------------------------------------\n");
}
