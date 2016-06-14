/*                               -*- Mode: C -*- 
 * 
 * Filename: material.h
 * Description: 
 * Author: Lunacie
 * Created: Mon Sep 28 21:35:28 2015 (+0200)
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


#ifndef			MATERIAL_H
#define			MATERIAL_H

#include		"textureMap.h"

typedef			struct s_material
{
  unsigned int		id;
  char			*name;

  t_textureMap		textureMaps[_TEXTUREMAPTYPE_SIZE];
}			t_material;


t_material		*getMaterial(char *name, char *prefix);
static t_material	*fillMaterial(FILE *file, t_material *material);

#endif			/* MATERIAL_H */
