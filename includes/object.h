/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:05:58 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/29 22:47:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vector.h"
# include "color.h"
# include "raycast.h"
# include "material.h"
# include "rt.h"

typedef enum	e_camera_type
{
	PERSPECTIVE,
	ORTHOGRAPHIC,
	FISHEYE
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
	LIGHT,
	MATERIAL,
	TEXTURE
}				t_object_type;

typedef struct	s_camera
{
	t_vec3			position;
	t_vec3			target;
	t_vec3			rotation;
	double			fov;
	t_camera_type	type;
	double			aspect;
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
	double			horizontal;
	double			vertical;
	double			focal_length;
	double			aperture;
}				t_camera;

typedef struct	s_light
{
	t_vec3			position;
	t_rgba			color;
	t_light_type	type;
	double			intensity;
	double			radius;
	double			leds;
}				t_light;

typedef struct	s_object
{
	t_object_type	type;
	void			*data;
}				t_object;

struct s_scene;

typedef void	(*t_object_func)(struct s_scene *scene, char *line, int n);

typedef struct	s_unique_obj
{
	char			obj_str[15];
	t_object_func	func;
	int				type;
}				t_unique_obj;

struct s_ray		get_camera_ray(struct s_scene *scene, t_camera *camera,
		double screen_x, double screen_y);
void				init_camera(t_vec3 origin, t_vec3 target,
		t_camera *camera, struct s_scene *scene);

#endif
