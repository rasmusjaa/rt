/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/31 17:57:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include "color.h"
# include "vector.h"
# include "mlx.h"
# include "raycast.h"
// # include "material.h"
# include "render.h"

# ifndef __linux__

#  define OS 0
# else
#  define OS 1
# endif

# define N_THREADS 10
# define EPSILON 0.0001
# define N_OBJ_TYPES 6
# define N_UNIQUE_OBJS 11
# define N_SCENE_VALUES 16
# define N_CAMERA_VALUES 14
# define N_SHAPE_VALUES 20
# define N_LIGHT_VALUES 10
# define N_MATERIAL_VALUES 17
# define N_TEXTURE_VALUES 14


# define MIN_WIDTH 800
# define MIN_HEIGHT 800
# define MAX_WIDTH 1600
# define MAX_HEIGHT 1200
# define MIN_COORD -100
# define MAX_COORD 100
# define MIN_CLIP 0.00001
# define MAX_CLIP 1000
# define MIN_SCALE 0.00001
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
# define MIN_BOUNCES 1
# define MAX_BOUNCES 100
# define CAMERA_TYPES 3
# define LIGHT_TYPES 2
# define SHAPE_TYPES 6
# define COLORIZES 7
# define RENDER_TILE_RES 20

# define SETTINGS_STR "settings"
# define CAMERA_STR "camera"
# define POINT_LIGHT_STR "point"
# define DIR_LIGHT_STR "directional"
# define PLANE_STR "plane"
# define SPHERE_STR "sphere"
# define CONE_STR "cone"
# define CYL_STR "cylinder"
# define DISC_STR "disc"
# define MODEL_STR "model"
# define MOEBIUS_STR "moebius"
# define SHAPE_ERROR_STR "shape_error"
# define MATERIAL_STR "material"
# define TEXTURE_STR "texture"

# define TRUE 1
# define FALSE 0

struct s_camera;
struct s_shape;
struct s_light;
struct s_tp;
struct s_queue;
struct s_mlx_img;
struct s_mesh;
struct s_texture;


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

typedef struct	s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
}				t_mlx;

typedef struct	s_asset_library
{
	struct s_texture	*textures;
	struct s_mesh		*meshes;
}				t_asset_library;

typedef struct	s_rt
{
	t_mlx 			*mlx;
	t_scene 		**scenes;
	size_t			num_scenes;
	size_t 			cur_scene;
	t_render_task	render_task;
	t_asset_library	assets;
	unsigned char	***grad_vectors;
	int				render_requested;
}				t_rt;

// typedef struct	s_thread
// {
// 	t_rt 			*rt;
// 	int				thread;
// }				t_thread;


void			reload_scene(t_rt *rt);
void			load_scene(t_rt *rt, int scene_nb);

void 			exit_message(char *str);
time_t			last_modified(char *file);
t_scene			*read_scene(t_rt *rt, char *file);

t_rt			*rt_init(size_t num_scenes);
int				perlin_init(t_rt *rt, struct s_texture *texture);
void			delete_gradient_vectors(unsigned char  ***g);
void			rt_destroy_exit(t_rt *rt, int status);

void			init_mlx(t_rt *rt);
void			create_mlx_window(t_rt *rt, int w, int h, char *title);

void			destroy_scene(t_rt *rt, t_scene *scene);

#endif
