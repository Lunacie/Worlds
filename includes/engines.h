/*                               -*- Mode: C -*- 
 * 
 * Filename: engines.h
 * Description: 
 * Author: Lunacie
 * Created: Tue Apr 29 23:35:22 2014 (+0200)
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


#ifndef		ENGINES
#define		ENGINES

#include	"program.h"
#include	"event.h"

typedef enum
  {
    GRAPHIC,
    GAME,
    MAPBUILDER,

    NB_ENGINES
  }e_engineType;

typedef		struct s_data
{
  bool		*exec;
  Event		*events;
}		t_data;

typedef struct s_engine
{
  e_engineType	type;
  int		(*update)(t_data *);
  void		(*destroy)(void);
}		t_engine;


t_engine			**initEngines(void);
int				updateEngines(t_engine **, bool *);
void				destroyEngines(t_engine **);

#endif		/* ENGINES */
