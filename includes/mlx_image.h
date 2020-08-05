/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:59:27 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/05 13:12:35 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IMAGE_H
# define MLX_IMAGE_H

# include "rt.h"
# include "color.h"
# include "mlx.h"

typedef enum	e_cube_map_face
{
	FRONT,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	BACK
}				t_cube_map_face;

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

t_mlx_img		*create_mlx_img(t_mlx *mlx, int width, int height);
t_mlx_img		*create_mlx_img_from_data(t_mlx *mlx, void *data,
					int width, int height);
void			destroy_mlx_img(t_mlx *mlx, t_mlx_img *mlx_img);
void			put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c);
int				get_pixel_mlx_img(t_mlx_img *img, int x, int y);
t_mlx_img		*load_file_to_mlx_img(t_mlx *mlx, char *file);
t_mlx_img		*load_xpm_to_mlx_img(t_mlx *mlx, char *file);
char			*img_load_ppm(char *filename, int *width, int *height);
int				ppm_bin_read_pixels(int fd, char *data,
					int *width, int *height);
int				ppm_read_pixels(int fd, char *data, int *width, int *height);
t_rgba			sample_cube_map(t_mlx_img *cube_map, t_vec3 v);

#endif
