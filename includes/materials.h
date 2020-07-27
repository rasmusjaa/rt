/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:09:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/27 17:17:56 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "rt.h"
# define CHECKER 1
# define BRICKS 2
# define PERLIN 3

typedef struct s_mlx_img	t_mlx_img;

typedef struct		s_texture
{
	size_t		id;
	char		*file;
	t_mlx_img	*img_data;
	int			procedural_type;
	//t_rgba		(*texture_function)(t_texture*, double, double);
	t_rgba		color1;
	t_rgba		color2;
	t_rgba		color3;
}					t_texture;

typedef struct		s_material
{
	size_t			id;
	t_rgba			diffuse;
	double			shininess;
	double			specular;
	int				texture_id;
	t_texture		*texture;
	double			refra_index;
	double			reflection;	
	double			opacity;
	double			uv_scale_x;
	double			uv_scale_y;
}					t_material;

typedef struct s_scene t_scene;

t_texture	new_texture(size_t id, size_t procedural, char *file, t_rgba col1, t_rgba col2, t_rgba col3);
t_material new_material(size_t id, t_rgba diffuse, t_texture *texture);

void	allocate_textures(t_scene *scene, size_t amount);
void	allocate_materials(t_scene *scene, size_t amount);


t_material *get_material_by_id(t_scene *scene, size_t id);
t_texture *get_texture_by_id(t_scene *scene, size_t id);

t_vec2		cylinder_uv(t_vec3 point, double max, double min);
t_vec2		sphere_uv(t_vec3 point);
t_vec2		plane_uv(t_vec3 point);
t_rgba		sample_texture(t_texture *texture, t_vec2 uv);

t_rgba		brick_texture(double u, double v);
double		perlin_noise(double x, double y, unsigned char ***g);
t_rgba checker_texture(t_texture *texture, double v, double u);

#endif
