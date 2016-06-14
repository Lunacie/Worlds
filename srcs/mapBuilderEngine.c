/*                               -*- Mode: C -*- 
 * 
 * Filename: mapBuilderEngine.c
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
#include		"mapBuilderEngine.h"
#include		"engines.h"
#include		"handle_error.h"
#include		"map.h"


t_engine		*initEngineMapBuilder(void)
{
  t_engine		*engine;
  t_mapBuilderData     	*data;

  // Init engine
  if (!(engine = malloc(sizeof(t_engine))))
    return raise_e(ERROR, MAPBUILDER_INIT_ERROR, NULL, "initEngineMapBuilder#1 - mapBuilderEngine.c");
  engine->type = MAPBUILDER;
  engine->update = &update;
  engine->destroy = &destroy;

  // Init MapBuilder data
  if (!(data = malloc(sizeof(t_mapBuilderData))))
    return raise_e(ERROR, MAPBUILDER_INIT_ERROR, NULL, "initEngineMapBuilder#2 - mapBuilderEngine.c");
  handleMapBuilderData(data);

  return engine;
}

static int		update(t_data *data)
{
  selectElementFromMap(data->events);
}

t_mapBuilderData		*handleMapBuilderData(t_mapBuilderData *tmp)
{
  static t_mapBuilderData	*data = NULL;

  if (!data)
    data = tmp;
  return data;
}

static void			destroy(void)
{
  t_mapBuilderData		*data;

  if ((data = handleMapBuilderData(NULL)))
    free(data);
}
