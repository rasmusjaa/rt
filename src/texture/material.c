/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:24:30 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/31 18:15:13 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "material.h"
#include "texture.h"
#include "color.h"
#include "scene.h"

t_material	new_material(size_t id, t_rgba diffuse, t_texture *texture)
{
	t_material mat;

	mat.id = id;
	mat.diffuse = diffuse;
	mat.shininess = 1;
	mat.specular = 1;
	mat.texture = texture;
	mat.opacity = 1;
	mat.normal_tex_id = 0;
	mat.bump_tex_id = 0;
	return (mat);
}

t_material	*get_material_by_id(t_scene *scene, size_t id)
{
	size_t i;

	i = 0;
	while (i < scene->num_materials)
	{
		if (scene->materials[i].id == id)
			return (&scene->materials[i]);
		i++;
	}
	return (NULL);
}
