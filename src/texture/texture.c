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

t_texture	*get_texture_by_id(t_scene *scene, size_t id)
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

t_rgba		sample_texture(t_texture *texture, t_vec2 uv)
{
	t_rgba	color;
	double	p;
	int		c;

	color = ft_make_rgba(0, 0, 0, 1);
	if (texture && texture->procedural_type == 0 && texture->img_data)
	{
		uv.x = uv.x - floor(uv.x);
		uv.y = uv.y - floor(uv.y);
		c = get_pixel_mlx_img(texture->img_data, uv.x *
			texture->img_data->width, uv.y * texture->img_data->height);
		color = ft_make_rgba((double)((c >> (16)) & 0xff) / 255.0,
			(double)((c >> (8)) & 0xff) / 255.0,
			(double)((c >> (0)) & 0xff) / 255.0, 1.0);
	}
	else if (texture->procedural_type == CHECKER)
		color = checker_texture(texture, uv.x, uv.y);
	else if (texture->procedural_type == BRICKS)
		color = brick_texture(texture, uv.x, uv.y);
	else if (texture->procedural_type == PERLIN)
	{
		p = o_perlin(texture, uv, texture->settings.x, texture->settings.y);
		color = ft_make_rgba(p, p, p, 1);
	}
	return (color);
}
