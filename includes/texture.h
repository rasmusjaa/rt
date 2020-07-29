/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:02:51 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/28 15:17:23 by wkorande         ###   ########.fr       */
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

struct s_mlx_img;

typedef struct			s_texture
{
	size_t				id;
	char				file[256];
	struct s_mlx_img	*img_data;
	int					procedural_type;
	t_rgba				color1;
	t_rgba				color2;
	t_vec3				settings;
}					t_texture;


t_texture				new_texture(size_t id, size_t procedural, char *file, t_rgba col1, t_rgba col2, t_rgba col3);
t_rgba					sample_texture(t_texture *texture, t_vec2 uv);

t_rgba					brick_texture(t_texture *texture, double u, double v);
double					perlin_noise(double x, double y, unsigned char ***g);
double					octave_perlin(double x, double y, int oct, double pers, unsigned char ***g);
t_rgba					checker_texture(t_texture *texture, double v, double u);

#endif
