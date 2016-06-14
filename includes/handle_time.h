/*                               -*- Mode: C -*- 
 * 
 * Filename: time.h
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  2 18:16:11 2014 (+0100)
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

#ifndef			TIME_H
#define			TIME_H

#ifndef			_TREEGENERATOR__
#include			"graphicEngine.h"
#endif			//_TREEGENERATOR__

long			getElapsedTime();
void			printFPS();
t_bool			isSecond(t_bool tmp, t_bool set);
static int		s_fps(int);

#endif			/* TIME_H */
