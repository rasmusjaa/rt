/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:02:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:05:00 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "rt.h"
# include "color.h"
# include "vector.h"

# define CHECKER 1
# define BRICKS 2
# define PERLIN 3
# define GRAD_MAX 10

struct s_mlx_img;

typedef struct			s_perlin_data
{
	double				grads_x[256];
	double				grads_y[256];
	int					perm[256];
}						t_perlin_data;

typedef struct			s_texture
{
	size_t				id;
	char				file[256];
	struct s_mlx_img	*img_data;
	int					procedural_type;
	t_rgba				color1;
	t_rgba				color2;
	t_vec3				settings;
	t_perlin_data		*perlin_data;
}						t_texture;

t_rgba					sample_texture(t_texture *texture, t_vec2 uv);
t_rgba					brick_texture(t_texture *texture, double u, double v);
double					perlin_noise(t_perlin_data *perlin, double x, double y);
double					o_perlin(t_texture *texture,
							t_vec2 uv, int oct, double pers);
t_rgba					checker_texture(t_texture *texture, double v, double u);

#endif
