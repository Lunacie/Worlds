/*                               -*- Mode: C -*- 
 * 
 * Filename: draw_map.c
 * Description: 
 * Author: Lunacie
 * Created: Sat Jan 24 17:43:25 2015 (+0100)
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


#include		"graphicEngine.h"
#include		"draw_map.h"
#include		"obj.h"
#include		"material.h"

int			draw_model(void)
{
  static t_obj		*obj = NULL;
  static t_material	*material = NULL;


  if (!obj)
    {
      if (obj = getObj("CitadelIsland", "",  TRIS))
      /* if (obj = getObj("tris",NULL,  TRIS)) */
      /* if (obj = getObj("Male", "", TRIS)) */
      /* if (obj = getObj("cat", "cat/", TRIS)) */
      /* if (obj = getObj("chunk00_00", NULL,  TRIS)) */
      /* if (obj = getObj("single_quad", NULL,  QUADS)) */
  	{
  	  debug("| | | | Map object retrived");

  	  if (!material)
  	    {
  	      if ( obj->materialName && (material = getMaterial(obj->materialName, "cat/")))
  	  	obj->materials = addToList(NULL, material);
	      
  	      else if (!obj->materialName)
  	  	debug("| | | | | No material to load for map");
  	      else
  	  	debug("| | | | | Could not load map material /!\\");
  	    }
  	}
    }
  if (obj)
    obj_draw(obj);
  else
    debug("| | | | Careful, Map is missing /!\\");
  return 0;
}
