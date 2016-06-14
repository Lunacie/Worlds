/*                               -*- Mode: C -*- 
 * 
 * Filename: debugHandling.h
 * Description: 
 * Author: Lunacie
 * Created: Fri Jan 30 20:53:58 2015 (+0100)
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

#ifndef			DEBUGHANDLING_H
#define			DEBUGHANDLING_H

#include		"program.h"
#include		<stdarg.h>

void			debug(char *str, ...);
bool			setDebug(bool value);
void			debugOncePerSecond(char *str, ...);

#endif			/* DEBUGHANDLING_H */
