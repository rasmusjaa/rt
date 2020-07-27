/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:41:54 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/27 17:19:40 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "materials.h"
#include "mlx_image.h"

void	allocate_textures(t_scene *scene, size_t amount)
{
	if (!(scene->textures = (t_texture*)malloc(sizeof(t_texture) * amount)))
		exit_message("Error allocating textures");
	scene->num_textures = amount;
}

t_texture	new_texture(size_t id, size_t procedural, char *file, t_rgba col1, t_rgba col2, t_rgba col3)
{
	t_texture tex;

	tex.id = id;
	tex.img_data = NULL;
	tex.color1 = col1;
	tex.color2 = col2;
	tex.color3 = col3;
	tex.file = file;
	if (tex.file)	
		return (tex);
	procedural = 1;
	/*
	if (procedural == BRICKS)
		tex.texture_function = brick_texture;
	else if (procedural == CHECKER)
		tex.texture_function = checker_texture;
	//else if (procedural == PERLIN)
	//	tex.texture_function = &perlin_noise;
	else
	{
		tex.texture_function = NULL;
	}
	*/
	return (tex);
}

t_texture *get_texture_by_id(t_scene *scene, size_t id)
{
	size_t i;

	i = 0;
	while (i < scene->num_textures)
	{
		if (scene->textures[i].id == id)
			return (scene->textures + i);
		i++;
	}
	return (NULL);
}

t_rgba	sample_texture(t_texture *texture, t_vec2 uv)
{
	t_rgba color;
	if (!texture || (!texture->procedural_type && !texture->img_data))
		return (ft_make_rgba(1, 1, 1, 1));
	if (texture && texture->procedural_type == 0 && texture->img_data)
	{
		int c = get_pixel_mlx_img(texture->img_data, uv.x * texture->img_data->width, uv.y * texture->img_data->height);
	   	color = ft_make_rgba(
					(double)((c >> (16)) & 0xff) / 255.0,
						(double)((c >> (8)) & 0xff) / 255.0,
							(double)((c >> (0)) & 0xff) / 255.0,
								1.0);	
		return (color);
	}
	if (texture->procedural_type == CHECKER)
		return (checker_texture(texture, uv.x, uv.y));

	return (ft_make_rgba(1, 1, 1, 1));
}
