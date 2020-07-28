/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:24:30 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/28 14:57:07 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "material.h"
#include "texture.h"
#include "color.h"

// void	material_temp_function(t_scene *scene)
// {
// 	t_rgba col1 = ft_make_rgba(1,1,1,1);
// 	t_rgba col2 = ft_make_rgba(0,0,0,0);
// 	t_rgba col3 = ft_make_rgba(1,0,0,1);

// 	if (!scene)
// 		return ;
// 	allocate_materials(scene, 2);
// 	allocate_textures(scene, 2);

// 	scene->textures[0] = new_texture(1, CHECKER, NULL, col1, col2, col3); 
// 	scene->materials[0] = new_material(1, ft_make_rgba(1, 0, 0, 1), scene->textures);
	
// 	scene->textures[1] = new_texture(2, BRICKS, NULL, col1, col2, col3); 
// 	scene->materials[1] = new_material(2, ft_make_rgba(1, 0, 0, 1), scene->textures + 1);

// }

// void	allocate_materials(t_scene *scene, size_t amount)
// {
// 	int i;

// 	i = 0;
// 	if(!(scene->materials = (t_material*)malloc(sizeof(t_material) * amount)))
// 		exit_message("Error allocating materials");
// 	scene->num_materials = amount;	
// }

t_material new_material(size_t id, t_rgba diffuse, t_texture *texture)
{
	t_material mat;

	mat.id = id;
	mat.diffuse = diffuse;
	mat.shininess = 200;
	mat.specular = 1;
	mat.texture = texture;
	mat.opacity = 1;
	return (mat);
}

t_material *get_material_by_id(t_scene *scene, size_t id)
{
	size_t i;

	i = 0;
	while (i < scene->num_materials)
	{
		if (scene->materials[i].id == id)
			return (scene->materials + i);
		i++;
	}
	return (NULL);
}
