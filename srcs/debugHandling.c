/*                               -*- Mode: C -*- 
 * 
 * Filename: debugHandling.c
 * Description: 
 * Author: Lunacie
 * Created: Fri Jan 30 20:53:01 2015 (+0100)
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

#include		<stdlib.h>
#include		<string.h>
#include		<stdio.h>
#include		<stdarg.h>

#include		"program.h"
#include		"debugHandling.h"
#include		"handle_time.h"

bool		handleDebug(bool value, bool change)
{
  static bool		debug = false;

  if (change == true)
    debug = value;
  return debug;
}

void			debug(char *str, ...)
{
  va_list argp;

  if (handleDebug(false, false))
  {
    va_start(argp, str);
    printf("debug : ");
    vprintf(str, argp);
    printf(" [x].\n");
    va_end(argp);
  }
}

void			debugOncePerSecond(char *str, ...)
{
  va_list argp;

  if (handleDebug(false, false))
  {
    if (isSecond(false, false))
      {
	va_start(argp, str);
	printf("debug : ");
	vprintf(str, argp);
	printf("\n");
	va_end(argp);
      }
  }
}

