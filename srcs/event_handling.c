/*                               -*- Mode: C -*- 
 * 
 * Filename: event_handling.c
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 15:13:46 2014 (+0100)
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
#include		<SDL/SDL.h>

#include		"program.h"
#include		"event.h"

#ifndef			_TREEGENERATOR__
#include		"graphicEngine.h"
#endif			/* _TREEGENERATOR__ */

/*
**			See https://wiki.libsdl.org/SDL_Keycode
*/

void			handle_events(bool *exec, Event *events)
{
  static SDL_Event event;
  Uint8 *keystates;

  keystates = SDL_GetKeyState(NULL);

  resetEvent(events);
  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	*exec = false;
      else if (event.type == SDL_KEYDOWN)
	{
	  // Directions
	  if (keystates[SDLK_LEFT])
	    events->left = true;
	  if (keystates[SDLK_UP])
	    events->up = true;
	  if (keystates[SDLK_RIGHT])
	    events->right = true;
	  if (keystates[SDLK_DOWN])
	    events->down = true;
	  
	  // Letters
	  if (keystates[SDLK_b])
	    events->key_b = true;
	  if (keystates[SDLK_d])
	    events->key_d = true;
	  if (keystates[SDLK_m])
	    events->key_m = true;
	  if (keystates[SDLK_s])
	    events->key_s = true;

	  // others
	  if (keystates[SDLK_LSHIFT])
	    events->shift = true;
	}
    }
  storeEvent(events, true);
}

void			resetEvent(Event *events)
{
  memset(events, 0, sizeof(Event));
}

Event			*storeEvent(Event *tmp, bool set)
{
  static Event		*event = NULL;

  if (tmp && set == true)
    event = tmp;
  return event;
}
