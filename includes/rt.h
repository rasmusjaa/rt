/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/06 14:08:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

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

# define N_OBJECTS 7
# define N_SCENE_VALUES 6
# define N_CAMERA_VALUES 14
# define N_SHAPE_VALUES 19
# define N_LIGHT_VALUES 8

# define MIN_WIDTH 320
# define MIN_HEIGHT 200
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define MIN_COORD -100
# define MAX_COORD 100
# define MIN_SCALE -10
# define MAX_SCALE 10
# define MIN_RADIUS 0.001
# define MAX_RADIUS 100
# define MIN_ANGLE 0
# define MAX_ANGLE 90
# define MIN_FOV 45
# define MAX_FOV 180
# define MIN_INTENSITY 0
# define MAX_INTENSITY 1000
# define MIN_ASPECT 0.5
# define MAX_ASPECT 2.0
# define CAMERA_TYPES 2
# define LIGHT_TYPES 2

# define MIN_BOUNCES 1
# define MAX_BOUNCES 100

typedef enum	e_camera_type
{
	PERSPECTIVE,
	ORTHOGRAPHIC
}				t_camera_type;

typedef enum	e_light_type
{
	POINT,
	DIRECTIONAL
}				t_light_type;

typedef enum	e_object_type
{
	SETTINGS,
	CAMERA,
	SHAPE,
	LIGHT
}				t_object_type;

typedef enum	e_shape_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	DISC
}				t_shape_type;


typedef struct		s_shape
{
	t_shape_type	type;
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	t_vec3			scale;
	t_rgba			color;
	double			radius;
	double			angle;
	double			opacity;
}					t_shape;

typedef	struct		s_scene_config
{
	char			*filepath;
	int				shadows;
	int				shading;
	int				specular;
	int				refraction;
	int				reflection;
	int				bounces;
}					t_scene_config;

typedef struct		s_camera
{
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	double			fov;
	t_camera_type	type;
	double			aspect;
	int				width;
	int				height;
}					t_camera;

typedef struct		s_light
{
	t_vec3			position;
	t_rgba			color;
	t_light_type	type;
	double			intensity;
}					t_light;

typedef struct		s_object
{
	t_object_type		type;
	void			*data;
}					t_object;

typedef struct		s_scene
{
	t_scene_config	scene_config;
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
	t_scene			**scenes;
	size_t			num_scenes;
}					t_rt;

typedef void		(*t_object_func)(t_scene *scene, char *line, int n);

typedef struct		s_objects
{
	char			object[5];
	t_object_func	func;
	int				type;
}					t_objects;

void				exit_message(char *str);
t_scene				*read_scene(char *file);
void				print_scene_info(t_scene *scene);

#endif
