/*                               -*- Mode: C -*- 
 * 
 * Filename: mapBuilderEngine.h
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 14:56:41 2014 (+0100)
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

#ifndef			MAPBUILDER_ENGINE_H
#define			MAPBUILDER_ENGINE_H

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>

#include		"handle_error.h"
#include		"debugHandling.h"
#include		"engines.h"
#include		"map.h"



t_engine		*initEngineMapBuilder(void);
static int		update(t_data *);
static void		destroy(void);

typedef			enum
  {
    VOXEL_CURSOR_MODE,
    CUBE_CURSOR_MODE,
    BLOCK_CURSOR_MODE,

    _NB_CURSOR_MODES
  }e_cursorSize;

typedef struct		s_cursor
{
  size_t		chunk;
  size_t		cube;
  size_t		voxel;

  e_cursorSize		size;
}			Cursor;


typedef			struct s_mapBuilderData
{
  Cursor		*cursor;  
}			t_mapBuilderData;


t_mapBuilderData	*handleMapBuilderData(t_mapBuilderData *tmp);
t_data			*handleData(t_data *tmp);

int			selectElementFromMap(Event *events);

void			moveCursor(Event *event, Cursor *cursor, Map *map);

#endif			/* MAPBUILDER_ENGINE_H */

