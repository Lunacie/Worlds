/*                               -*- Mode: C -*- 
 * 
 * Filename: map.h
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

#ifndef			MAP_H
#define			MAP_H

#include		<unistd.h>

#define			MULTIPLIER	4
#define			SIZE		MULTIPLIER * MULTIPLIER * MULTIPLIER

/* #define			FAR		8 */

/* typedef			char		Voxel; */

/* typedef			Voxel		Cube[SIZE]; */
/* typedef			Cube		Chunk[SIZE][SIZE]; */

typedef struct		s_map
{
  /* Chunk			chunks[FAR]; */
  char			***buffer;
  size_t		size;
  struct s_octreeNode	*octree;
  

  size_t		nbChunks;
  size_t		nbVoxelsPerChunk;
  size_t		edgeSize;
  size_t		subdivisions;
  

  /* size_t		nbCubesPerChunks; */
  /* size_t		nbVoxelsPerCubes; */
  /* size_t		multiplier; */
}			Map;

Map			*initMap();
void			setVoxel(Map *map, size_t chunk, size_t cube, size_t voxel, char type);
char			getVoxel(Map *map, size_t chunk, size_t cube, size_t voxel);
void			printMap(Map *map);

bool			cubeIsFull(Map *map, size_t chunk, size_t cube);
bool			chunkIsFull(Map *map, size_t chunk);

#endif			/* MAP_H */
