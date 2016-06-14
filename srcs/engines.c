/*                               -*- Mode: C -*- 
 * 
 * Filename: engines.c
 * Description: 
 * Author: Lunacie
 * Created: Tue Apr 29 23:45:42 2014 (+0200)
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

#include		"engines.h"
#include		"graphicEngine.h"
#include		"gameEngine.h"

t_engine			**initEngines(void)
{
  t_engine		**engines;

  if (!(engines = malloc(sizeof(t_engine *) * NB_ENGINES)))
    {
      raise_e(ERROR, MALLOC_FAILED, NULL, "initEngine - engines.c");
      return raise_e(ERROR, ENGINE_INIT_ERROR, NULL, "initEngine - engines.c");
    }
  handleData(NULL);

  engines[GAME] = initEngineGame();
  debug("| Game Engine was succesfully intitialized");

  engines[GRAPHIC] = initEngineGraphic();
  debug("| Graphic Engine was succesfully intitialized");

  engines[MAPBUILDER] = initEngineMapBuilder();
  debug("| Map Builder Engine was succesfully intitialized");

  return engines;
}

int				updateEngines(t_engine **engines, bool *exec)
{
  int				x = 0;
  t_data			*data = handleData(NULL);

  data->exec = exec;
  while (x < NB_ENGINES)
    {
      if (engines[x])
	engines[x]->update(data);
      x++;
    }
}

void				destroyEngines(t_engine **engines)
{
  int				x = 0;

  while (x < NB_ENGINES)
    {
      if (engines[x])
	engines[x]->destroy();
      x++;
    }
}

t_data				*handleData(t_data *tmp)
{
  static t_data			*data = NULL;

  if (!data)
    {
      if (!(data = malloc(sizeof(t_data))))
	return raise_e(ERROR, MALLOC_FAILED, NULL, "handleData #1 - engines.c");
      if (!(data->events = malloc(sizeof(Event))))
	return raise_e(ERROR, MALLOC_FAILED, NULL, "handleData #2 - engines.c");
    }
  if (tmp)
    data = tmp;
  return data;
}
