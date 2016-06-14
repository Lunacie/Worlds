/*                               -*- Mode: C -*- 
 * 
 * Filename: event.h
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 16:48:32 2014 (+0100)
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


#ifndef			EVENT_H
#define			EVENT_H

#include		"program.h"

typedef			char bool;

typedef	struct		s_event
{
  //			Directions
  bool			left;
  bool			right;
  bool			up;
  bool			down;

  //			Letters
  bool			key_b;
  bool			key_d;
  bool			key_s;
  bool			key_m;

  //			others
  bool			shift;
}			Event;

void			resetEvent(Event *event);
void			handle_events(bool *exec, Event *events);
Event			*storeEvent(Event *tmp, bool set);

#endif			/* EVENT_H */
