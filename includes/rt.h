/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/15 17:03:26 by wkorande         ###   ########.fr       */
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
# include "thread_pool.h"

# define N_THREADS 10

# define N_OBJ_TYPES 4
# define N_UNIQUE_OBJS 8
# define N_SCENE_VALUES 8
# define N_CAMERA_VALUES 12
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
# define MIN_BOUNCES 1
# define MAX_BOUNCES 100
# define CAMERA_TYPES 2
# define LIGHT_TYPES 2
# define SHAPE_TYPES 5

# define SETTINGS_STR "settings"
# define CAMERA_STR "camera"
# define POINT_LIGHT_STR "point"
# define DIR_LIGHT_STR "directional"
# define PLANE_STR "plane"
# define SPHERE_STR "sphere"
# define CONE_STR "cone"
# define CYL_STR "cylinder"
# define DISC_STR "disc"
# define MOEBIUS_STR "moebius"
# define SHAPE_ERROR_STR "shape_error"

# define TRUE 1
# define FALSE 0

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
	char			*name;
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
	int				width;
	int				height;
}					t_scene_config;

typedef struct		s_camera
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
}					t_camera;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

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
	size_t			num_all[N_OBJ_TYPES];
	t_object		*objects;
	size_t			num_objects;
	t_camera		*cameras;
	size_t			num_cameras;
	size_t			cur_camera;
	t_light			*lights;
	size_t			num_lights;
	t_shape			*shapes;
	size_t			num_shapes;
}					t_scene;

typedef struct	s_mlx_img
{
	void		*img;
	char		*d_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_mlx_img;

typedef struct		s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
}					t_mlx;

typedef struct		s_rt
{
	t_mlx 			*mlx;
	t_mlx_img		*mlx_img;
	t_scene 		**scenes;
	size_t			num_scenes;
	size_t 			cur_scene;
	t_tp			*tp_render;
	t_queue			*done_tiles;
}					t_rt;

typedef struct	s_raycast_hit
{
	t_vec3		point;
	t_vec3		normal;
	t_shape		*shape;
	t_vec3		light_dir;
	double		t;
	double		t2;
	double		distance;
	t_rgba		color;
}				t_raycast_hit;

typedef struct	s_tile_job_data
{
	t_rt			*rt;
	t_mlx			*mlx;
	t_scene			*scene;
	t_mlx_img		*mlx_img;
	t_vec2i			screen_coord;
	t_vec2i			tile_size;
	int				tile_index;
	int				*jobs;
	pthread_mutex_t	*job_mutex;
	t_camera		*camera;
}					t_tile_job_data;

typedef struct		s_thread
{
	t_rt 			*rt;
	int				thread;
}					t_thread;

typedef void		(*t_object_func)(t_scene *scene, char *line, int n);

typedef struct		s_unique_obj
{
	char			obj_str[15];
	t_object_func	func;
	int				type;
}					t_unique_obj;

typedef struct		s_shape_name_type_map
{
	char			name[20];
	t_shape_type	type;
}					t_shape_name_type_map;

void hooks_and_loop(t_rt *rt);
void refresh_scene(t_rt *rt, int scene_nb, char *file);
void load_scene(t_rt *rt, int scene_nb);

void exit_message(char *str);
t_scene				*read_scene(char *file);

void				print_scene_info(t_scene *scene);
void				print_vec3(char *s, t_vec3 v);
void				print_rgba(char *s, t_rgba c);

int mouse_press_hook(int button, int x, int y, t_rt *rt);
int mouse_release_hook(int button, int x, int y, t_rt *rt);
int mouse_move_hook(int x, int y, t_rt *rt);

int key_press_hook(int key, t_rt *rt);
int key_release_hook(int key, t_rt *rt);

int	close_hook(t_rt *rt);
int expose_hook(t_rt *rt);

t_ray	get_camera_ray(t_scene *scene, t_camera *camera, t_vec2i screen_coord);
void	init_camera(t_vec3 origin, t_vec3 target, t_camera *camera);

t_mlx_img		*create_mlx_image(t_mlx *mlx, int width, int height);
void			put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);

t_rt			*rt_init(size_t num_scenes);
void			rt_destroy_exit(t_rt *rt, int status);

void			render_scene(t_rt *rt, t_scene *scene);

t_rgba			raycast(t_ray *ray, t_scene *scene);
int				intersects_shape(t_ray *ray, t_shape *shape, t_raycast_hit *hit);
#endif
