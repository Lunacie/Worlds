/*                               -*- Mode: C -*- 
 * 
 * Filename: time.c
 * Description: 
 * Author: Lunacie
 * Created: Sun Feb  9 15:58:57 2014 (+0100)
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

#include		<sys/time.h>

#include		"program.h"

#include		"handle_time.h"

long			getElapsedTime()
{
  static bool first = true;
  static struct timeval start;
  struct timeval  end;
  long mtime, seconds, useconds;    

  if (first)
    {
      first = false;
      gettimeofday(&start, NULL);
    }
  gettimeofday(&end, NULL);

  seconds  = end.tv_sec  - start.tv_sec;
  useconds = end.tv_usec - start.tv_usec;

  mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
  return mtime;
}

static int		s_fps(int tmp)
{
  static int value = 0;

  if (tmp)
    value = tmp;
  return value;
}

t_bool		isSecond(t_bool tmp, t_bool set)
{
  static int value = 0;

  if (set)
    value = tmp;
  return value;
}

void			printFPS()
{
  static long		relay = 0;
  long			time = getElapsedTime();
  static int		frames = 1;

  isSecond(false, true);
  if (!relay)
    relay = getElapsedTime();
  if (time - relay > 1000) // Si ça fait une seconde
    {
      isSecond(true, true);
      relay = getElapsedTime();
      s_fps(frames);
      printf("FPS : %d\n", frames);
      frames = 0;
    }
  frames += 1;
}
