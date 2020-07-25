/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/07/25 11:57:36 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <sys/time.h>
# include "color.h"
# include "vector.h"
# include "mlx.h"
# include "raycast.h"

# ifndef __linux__

#  define OS 0
# else
#  define OS 1
# endif

# define N_THREADS 10
# define EPSILON 0.0001
# define N_OBJ_TYPES 4
# define N_UNIQUE_OBJS 9
# define N_SCENE_VALUES 13
# define N_CAMERA_VALUES 12
# define N_SHAPE_VALUES 20
# define N_LIGHT_VALUES 10

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

# define TRUE 1
# define FALSE 0

struct s_camera;
struct s_shape;
struct s_light;
struct s_tp;
struct s_queue;

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
}				t_scene_config;

typedef struct	s_scene
{
	t_scene_config	scene_config;
	size_t			num_all[N_OBJ_TYPES];
	struct s_camera	*cameras;
	size_t			num_cameras;
	size_t			cur_camera;
	struct s_light	*lights;
	size_t			num_lights;
	struct s_shape	*shapes;
	size_t			num_shapes;
	int				help_ray;
}				t_scene;

typedef struct	s_mlx_img
{
	void			*img;
	char			*d_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_mlx_img;

typedef struct	s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				bpp;
	int				size_line;
	int				endian;
}				t_mlx;

typedef struct	s_tile_job_data
{
	struct s_rt		*rt;
	t_mlx			*mlx;
	t_scene			*scene;
	t_mlx_img		*mlx_img;
	t_vec2i			screen_coord;
	t_vec2i			tile_size;
	int				tile_index;
	int				*jobs;
	pthread_mutex_t	*task_mutex;
	struct s_camera	*camera;
}				t_tile_job_data;

typedef struct	s_render_task
{
	struct timeval	start_time;
	struct timeval	end_time;
	struct s_tp		*thread_pool;
	t_tile_job_data *job_data_block;
	pthread_mutex_t task_mutex;
	int				jobs;
	int				num_jobs;
	struct s_queue	*done_tiles;
	size_t			render_finished;
	size_t			render_started;
}				t_render_task;

typedef struct	s_rt
{
	t_mlx 			*mlx;
	t_scene 		**scenes;
	size_t			num_scenes;
	size_t 			cur_scene;
	t_render_task	render_task;
}				t_rt;

typedef struct	s_thread
{
	t_rt 			*rt;
	int				thread;
}				t_thread;

void 			hooks_and_loop(t_rt *rt);
void			reload_scene(t_rt *rt);
void			load_scene(t_rt *rt, int scene_nb);

void 			exit_message(char *str);
time_t			last_modified(char *file);
t_scene			*read_scene(char *file);

t_mlx_img		*create_mlx_img(t_mlx *mlx, int width, int height);
t_mlx_img		*create_mlx_img_from_data(t_mlx *mlx, void *data, int width, int height);
void			destroy_mlx_img(t_mlx *mlx, t_mlx_img *mlx_img);
void			put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);
int				get_pixel_mlx_img(t_mlx_img *img, int x, int y);

t_rt			*rt_init(size_t num_scenes);
void			rt_destroy_exit(t_rt *rt, int status);
void			render_scene(t_rt *rt, t_scene *scene);
void			destroy_scene(t_scene *scene);

#endif
