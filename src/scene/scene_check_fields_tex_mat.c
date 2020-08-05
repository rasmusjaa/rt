/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_check_fields_tex_mat.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 13:18:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:19:15 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "object.h"
#include "shape.h"
#include "texture.h"
#include "mlx_image.h"
#include "libft.h"
#include "ft_printf.h"
#include "mesh.h"
#include "object.h"
#include "obj_loader.h"

void	check_texture_fields(t_scene *scene, char *line, int n)
{
	double		values[N_TEXTURE_VALUES];
	t_texture	*tx;
	char		*file_pointer;
	size_t		i;

	tx = &scene->textures[n];
	get_fields(line, values, N_TEXTURE_VALUES);
	tx->id = round(values[0]);
	tx->procedural_type = round(values[1]);
	tx->color1 = ft_clamp_rgba(ft_make_rgba(values[2], values[3], values[4], values[5]));
	tx->color2 = ft_clamp_rgba(ft_make_rgba(values[6], values[7], values[8], values[9]));
	tx->settings = ft_clamp_vec3(ft_make_vec3(values[10], values[11], values[12]), 0, 100);
	ft_bzero(tx->file, 256);
	tx->img_data = NULL;
	tx->perlin_data = NULL;
	if (tx->procedural_type == PERLIN)
	{
			if (perlin_init(scene->rt, tx) == -1)
				exit_message("error initializing gradient vectors");
	}
	if (!tx->procedural_type)
	{
		file_pointer = get_shape_file(line, N_TEXTURE_VALUES);
		if (file_pointer == NULL)
			exit_message("no texture on texture line");
		i = 0;
		while(file_pointer[0 + i] != '\n' && file_pointer[0 + i] != ';' && file_pointer[0 + i] != 0)
			i++;
		ft_strncpy(tx->file, file_pointer, i);
		tx->file[i] = 0;
		tx->img_data = load_file_to_mlx_img(scene->rt->mlx, tx->file);
	}
}

void	check_material_fields(t_scene *scene, char *line, int n)
{
	double		values[N_MATERIAL_VALUES];
	t_material	*mat;

	mat = &scene->materials[n];
	get_fields(line, values, N_MATERIAL_VALUES);
	mat->id = round(values[0]);
	mat->texture_id = round(values[1]);
	mat->diffuse = ft_clamp_rgba(ft_make_rgba(values[2], values[3], values[4], values[5]));
	mat->shininess = ft_clamp_d(values[6], 0, 1);
	mat->refra_index = ft_clamp_d(values[7], 1, 6);
	mat->reflection = ft_clamp_d(values[8], 0, 1);
	mat->opacity = ft_clamp_d(values[9], 0, 1);
	mat->u_scale = ft_clamp_d(values[10], 0.01, 100);
	mat->v_scale = ft_clamp_d(values[11], 0.01, 100);
	mat->explode = ft_clamp_d(values[12], 0, 5);
	mat->normal_tex_id = round(ft_clamp_d(values[13], 0, 100));
	mat->normal_mult = ft_clamp_d(values[14], 0, 90);
	mat->bump_tex_id = round(ft_clamp_d(values[15], 0, 100));
	mat->bump_mult = ft_clamp_d(values[16], 0, 100);
	mat->texture = NULL;
}
