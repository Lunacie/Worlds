/*                               -*- Mode: C -*- 
 * 
 * Filename: gameEngine.h
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

#ifndef			GAME_ENGINE_H
#define			GAME_ENGINE_H

#include		<SDL/SDL.h>
#include		<GL/gl.h>
#include		<GL/glu.h>

#include		"map.h"
#include		"program.h"
#include		"handle_error.h"
#include		"engines.h"


t_engine		*initEngineGame(void);
static int		update(t_data *);
static void		destroy(void);

typedef			struct s_gameData
{
  Map			*map;
}			t_gameData;

t_gameData		*handleGameData(t_gameData *tmp);
t_data			*handleData(t_data *tmp);

#endif			/* GAME_ENGINE_H */

