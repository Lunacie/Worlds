/*                               -*- Mode: C -*- 
 * 
 * Filename: graphicEngine.c
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
#include		"graphicEngine.h"
#include		"engines.h"
#include		"handle_error.h"
#include		"time.h"

/* WINDOW INFORMATIONS */

/* #define			WIDTH		1920 */
/* #define			HEIGHT		1080 */
#define			WIDTH		960
#define			HEIGHT		540


t_engine		*initEngineGraphic(void)
{
  t_engine		*engine;
  t_graphicData		*data;
  SDL_Surface		*screen;

  // Init engine
  if (!(engine = malloc(sizeof(t_engine))))
    return raise_e(ERROR, GRAPHIC_INIT_ERROR, NULL, "initEngineGraphic#1 - graphicEngine.c");
  engine->type = GRAPHIC;
  engine->update = &update;
  engine->destroy = &destroy;

  // init SDL
  if (!(screen = initScreen(WIDTH, HEIGHT)))
    return raise_e(ERROR, SDL_INIT_ERROR, NULL, "initEngineGraphic - graphicEngine.c");

  // Init Graphic data
  if (!(data = malloc(sizeof(t_graphicData))))
    return raise_e(ERROR, GRAPHIC_INIT_ERROR, NULL, "initEngineGraphic#2 - graphicEngine.c");
  data->screen = screen;
  handleGraphicData(data);

  return engine;
}

static int		update(t_data *data)
{
  prepareScreen();
  handle_camera(data->events);
  draw();
  printFPS();
}

t_graphicData		*handleGraphicData(t_graphicData *tmp)
{
  static t_graphicData	*data = NULL;

  if (!data)
    data = tmp;
  return data;
}

static void			destroy(void)
{
  SDL_Quit();
}
