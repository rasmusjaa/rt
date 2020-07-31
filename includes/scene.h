/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 18:09:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/31 18:14:41 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "rt.h"
# include <stdlib.h>
# include <sys/time.h>
# include "color.h"

typedef	struct	s_scene_config
{
	char			*filepath;
	time_t			last_modified;
	int				shadows;
	int				shading;
	int				specular;
	int				opacity;
	int				refraction;
	int				reflection;
	int				bounces;
	int				width;
	int				height;
	t_rgba			ambient;
	size_t			colorize;
	size_t			sky_tex_id;
	int				dof;
	size_t			dof_samples;
}				t_scene_config;

struct s_rt;

typedef struct	s_scene
{
	t_scene_config		scene_config;
	size_t				num_settings;
	size_t				num_all[N_OBJ_TYPES];
	struct s_camera		*cameras;
	size_t				num_cameras;
	size_t				cur_camera;
	struct s_light		*lights;
	size_t				num_lights;
	struct s_shape		*shapes;
	size_t				num_shapes;
	int					help_ray;
	struct s_material	*materials;
	size_t				num_materials;
	struct s_texture	*textures;
	size_t				num_textures;
	struct s_texture	*cube_map;
	struct s_rt			*rt;
}					t_scene;

t_scene			*read_scene(t_rt *rt, char *file);
void			reload_scene(t_rt *rt);
void			destroy_scene(t_rt *rt, t_scene *scene);

#endif
