/*                               -*- Mode: C -*- 
 * 
 * Filename: list.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Jun 20 12:52:54 2015 (+0200)
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

#include			"program.h"
#include			"graphicEngine.h"
#include			"list.h"

t_list				*addToList(t_list *list, void *content)
{
  t_list			*new;
  t_list			*current;
  t_list			*prev;

  if (!(new = malloc(sizeof(t_list))))
    return NULL;
  new->content = content;
  new->next = NULL;
  new->prev = NULL;
  prev = NULL;
  current = list;
  while (current)
    {
      prev = current;
      current = current->next;
    }
  if (prev)
    {
      prev->next = new;
      new->prev = prev;
    }
  else
    list = new;
  return list;
}

t_list				*addBeforeList(t_list *list, void *content)
{
  t_list			*new;
  t_list			*current;
  t_list			*prev;

  if (!(new = malloc(sizeof(t_list))))
    return NULL;
  new->content = content;
  new->next = list;
  new->prev = NULL;
  prev = NULL;
  list->prev = new;
  return new;
}

t_list				*getLastElement(t_list *list)
{
  while (list)
    {
      if (!list->next)
	return list;
      list = list->next;
    }
  return NULL;
}

t_list			*addListToList(t_list *list1, t_list *list2)
{
  t_list		*tmp;

  if (!list2 || !list1)
    return NULL;
  tmp = list1;
  while (list1 && list1->next)
    list1 = list1->next;
  list1->next = list2;
    list2->prev = list1;
  return tmp;
}

char			*listToString(t_list *list)
{
  size_t		len;
  char			*str;
  size_t		x;
  size_t		y;
  t_list		*tmp;
  char			*tmp_str;


  len = 0;
  tmp = list;
  while (list)
    {
      if (list->content)
	len += strlen(list->content);
      list = list->next;
    }
  list = tmp;
  if (!(str = malloc(len + 1)))
    return NULL;
  x = 0;
  while (list)
    {
      if (list->content)
	{
	  tmp_str = (char *)list->content;
	  y = 0;
	  while (tmp_str[y])
	    {
	      str[x] = tmp_str[y];
	      x++;
	      y++;
	    }
	}
      list = list->next;
    }
  str[x] = '\0';
  return str;
}


t_list			*addListAfterElement(t_list *list1, t_list *list2)
{
  t_list		*next;

  if (!list1 || !list2)
    return NULL;
  next = list1->next;
  list1->next = list2;
  list2->prev = list1;
  while (list2 && list2->next)
    list2 = list2->next;
  list2->next = next;
  return list1;
}


t_list			*addListInPlaceOfElement(t_list *list1, t_list *list2)
{
  t_list		*next;
  t_list		*prev;
  t_list		*ret;

  if (!list1 || !list2)
    return NULL;
  next = list1->next;
  prev = list1->prev;
  free(list1);
  list2->prev = prev;
  ret = list2;
  while (list2 && list2->next)
    list2 = list2->next;
  list2->next = next;
  return ret;
}

t_list			*getFirstElement(t_list *list)
{
  while (list && list->prev)
    {
      /* printf("looking for first : %d\n", list->prev); */
      /* printf("reverse: %s\n", list->content); */
      list = list->prev;
    }
  return list;
}


void				destroyList(t_list *list, bool allocated)
{
  while (list)
    {
      if (list->content && allocated == true)
	{
	  free(list->content);
	  list->content = NULL;
	}
      list = list->next;
      if (list)
	{
	  free(list->prev);
	  list->prev = NULL;
	}
    }
}
