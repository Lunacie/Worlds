/*                               -*- Mode: C -*- 
 * 
 * Filename: initScreen.c
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 15:08:58 2014 (+0100)
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

#ifndef			_TREEGENERATOR__
#include			"graphicEngine.h"
#endif			/* _TREEGENERATOR__ */


#ifdef			_TREEGENERATOR__
#include			"treeGenerator.h"
#include			"graphic.h"
#endif			/* _TREEGENERATOR__ */

#include		"event.h"


SDL_Surface		*initScreen(int width, int height)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  SDL_Flip(screen);
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  glMatrixMode(GL_PROJECTION);

  /* glEnable(GL_STENCIL_TEST); */
  /* glEnable(GL_CULL_FACE); */

  /* glEnable(GL_LIGHTING); */
  /* glEnable(GL_LIGHT0);  */

  debug("| | SDL was succesfully intitialized");
  return (screen);
}

void			prepareScreen()
{
  glDepthMask(GL_TRUE);

  /* glEnable(GL_STENCIL_TEST); */
  /* glEnable(GL_CULL_FACE); */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void			flushScreen()
{
  glFlush();
  SDL_GL_SwapBuffers();
}
