/*                               -*- Mode: C -*- 
 * 
 * Filename: gameEngine.c
 * Description: 
 * Author: Lunacie
 * Created: Wed Apr 30 00:19:16 2014 (+0200)
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

#include		<unistd.h>
#include		<stdlib.h>

#include		"program.h"
#include		"gameEngine.h"
#include		"engines.h"
#include		"handle_error.h"
#include		"time.h"

t_engine		*initEngineGame(void)
{
  t_engine		*engine;
  t_gameData		*data;
  SDL_Surface		*screen;
  Event			*events;

  // Init engine
  if (!(engine = malloc(sizeof(t_engine))))
    return raise_e(ERROR, GAME_INIT_ERROR, NULL, "initEngineGame#1 - gameEngine.c");
  engine->type = GAME;
  engine->update = &update;
  engine->destroy = &destroy;

  // Init Game data
  if (!(data = malloc(sizeof(t_gameData))))
    return raise_e(ERROR, GAME_INIT_ERROR, NULL, "initEngineGame#1 - gameEngine.c");
  data->map = initMap();
  handleGameData(data);
  return engine;
}

static int		update(t_data *data)
{
  handle_events(data->exec, data->events);
  /* debug("| | Game engine update > events update "); */
}


/*
** Will contain the map
** Informations about the player
** Stuff like that
*/

t_gameData		*handleGameData(t_gameData *tmp)
{
  static t_gameData	*data = NULL;

  if (tmp)
    data = tmp;
  return data;
}


static void		destroy(void)
{

}
