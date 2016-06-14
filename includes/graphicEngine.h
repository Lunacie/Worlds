/*                               -*- Mode: C -*- 
 * 
 * Filename: graphicEngine.h
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

#ifndef			GRAPHIC_ENGINE_H
#define			GRAPHIC_ENGINE_H

#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>

#include		<SDL/SDL.h>
#include		<GL/gl.h>
#include		<GL/glu.h>

#include		"handle_error.h"
#include		"debugHandling.h"
#include		"engines.h"



int			draw();

SDL_Surface		*initScreen(int width, int height);
void			prepareScreen();
void			flushScreen();

t_engine		*initEngineGraphic(void);
static int		update(t_data *);
static void		destroy(void);

typedef			struct s_graphicData
{
    SDL_Surface		*screen;
}			t_graphicData;

typedef			struct s_vertex
{
  float			x;
  float			y;
  int			id;
  float			z;
}			t_vertex;

typedef			struct s_uv
{
  float			x;
  float			y;
  int			id;
}			t_uv;

typedef			struct s_faceVertex
{
  t_vertex		*v;
  t_vertex		*vt;
  t_vertex		*vn;
  char			str[1024];
}			t_faceVertex;

typedef			struct s_face
{
  int			nb_vertex;
  t_faceVertex		faceVertex[3];
}			t_face;



t_graphicData		*handleGraphicData(t_graphicData *tmp);
t_data			*handleData(t_data *tmp);

#endif			/* GRAPHIC_ENGINE_H */

