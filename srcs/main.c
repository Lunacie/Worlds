
/*                               -*- Mode: C -*- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Lunacie
 * Created: Thu Jan 16 02:45:28 2014 (+0100)
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
#include		<string.h>

#include		"engines.h"
#include		"graphicEngine.h"
#include		"event.h"
#include		"time.h"
#include		"debugHandling.h"

char			*binary = NULL;

int			main(int argc, char **argv)
{
  t_engine		**engines;
  bool			exec;
  size_t		i;

  for(i = 0; argv[i]; i++)
    if (!strcmp("-v", argv[i]))
      handleDebug(true, true);
  binary = argv[0];
  engines = initEngines();
  exec = true;
  while (exec)
    {
      /* debug("| In Exec Loop : "); */
      updateEngines(engines, &exec);
      /* debug("| Engine were updated"); */
      if (handleProgramStatus(NONE) == ERROR)
	return abortProgram();
    }
  destroyEngines(engines);
  debug("| Engine were destroyed. Bye !");
  return 0;
}
