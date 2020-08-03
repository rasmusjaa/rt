/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:41:54 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/31 18:14:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "material.h"
#include "mlx_image.h"
#include "libft.h"
#include "scene.h"


// void	allocate_textures(t_scene *scene, size_t amount)
// {
// 	if (!(scene->textures = (t_texture*)malloc(sizeof(t_texture) * amount)))
// 		exit_message("Error allocating textures");
// 	scene->num_textures = amount;
// }

t_texture	new_texture(size_t id, size_t procedural, char *file, t_rgba col1, t_rgba col2, t_rgba col3)
{
	t_texture tex;

	tex.id = id;
	tex.img_data = NULL;
	tex.color1 = col1;
	tex.color2 = col2;
	col3.r = 0;
	tex.settings = ft_make_vec3(1, 0.5, 0);
	ft_strcpy(tex.file, file);
	procedural = 0;
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

	if (!scene)
		return (NULL);
	i = 0;
	while (i < scene->num_textures)
	{
		if (scene->textures[i].id == id)
			return (&scene->textures[i]);
		i++;
	}
	return (NULL);
}

t_rgba	sample_texture(t_texture *texture, t_vec2 uv)
{
	t_rgba color;
	double perlin;

	if (!texture || (!texture->procedural_type && !texture->img_data))
		return (ft_make_rgba(0, 0, 0, 1));
	if (texture && texture->procedural_type == 0 && texture->img_data)
	{
		uv.x = uv.x - floor(uv.x);
		uv.y = uv.y - floor(uv.y);
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
	if (texture->procedural_type == BRICKS)
		return (brick_texture(texture, uv.x, uv.y));
	if (texture->procedural_type == PERLIN)
	{
		perlin = octave_perlin(texture, uv, texture->settings.x, texture->settings.y);
		//perlin = perlin_noise(texture, uv.x * GRAD_MAX, uv.y * GRAD_MAX);
		color = ft_make_rgba(perlin, perlin, perlin, 1);
		return (color);
	}
	return (ft_make_rgba(0, 0, 0, 1));
}
