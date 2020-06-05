/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/05 16:17:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define N_OBJECTS 7
# define N_SCENE_VALUES 6
# define N_CAMERA_VALUES 14
# define N_SHAPE_VALUES 19
# define N_LIGHT_VALUES 8

# define MIN_COORD -100
# define MAX_COORD 100
# define MIN_SCALE -10
# define MAX_SCALE 10
# define MIN_RADIUS 0.001
# define MAX_RADIUS 100
# define MIN_ANGLE 0
# define MAX_ANGLE 90

# include "color.h"
# include "ft_get_next_line.h"
# include "ft_hashtable.h"
# include "ft_printf.h"
# include "ft_queue.h"
# include "ft_stack.h"
# include "libft.h"
# include "matrix.h"
# include "vector.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

typedef enum	e_camera_type
{
	PERSPECTIVE,
	ORTHOGRAPHIC
}

typedef enum	e_light_type
{
	POINT,
	DIRECTIONAL
}

typedef enum	e_obj_type
{
	SCENE,
	CAMERA,
	SHAPE,
	LIGHT
}

typedef enum	e_shape_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	DISC
}

typedef void		(*t_object_func)(char *line);

typedef struct		s_shape
{
	e_shape_type	shape_type;
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	t_vec3			scale;
	t_rgba			color;
	double			radius;
}					t_shape;

typedef				s_scene
{
	int				shadows;
	int				shading;
	int				speculars;
	int				refraction;
	int				reflection;
	int				bounces;
}					t_scene;

typedef				s_camera
{
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	double			fov;
	e_camera_type	type;
	double			aspect;
	double			width;
	double			height;
}					t_camera;

typedef				s_light
{
	t_vec3			position;
	t_rgba			color;
	e_light_type	type;
	int				intensity;
}					t_light;

typedef struct		s_object
{
	e_obj_type		type;
	void			*data;
}					t_object;

typedef struct		s_scene
{
	size_t			num_all[4];
	t_object		*objects;
	size_t			num_objects;
	t_camera		*cameras;
	size_t			num_cameras;
	t_light			*lights;
	size_t			num_lights;
	t_shape			*shapes;
	size_t			num_shapes;
}					t_scene;

typedef struct		s_rt
{
	t_scene			*scenes;
	size_t			num_scenes;
}					t_rt;




typedef struct		s_objects
{
	char			object[5];
	t_object_func	func;
	int				type;
}					t_objects;

void exit_message(char *str);
t_scene		*read_scene(char *file, t_rt *rt);

#endif
