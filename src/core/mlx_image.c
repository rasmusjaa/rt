/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:00:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 16:19:48 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include <stdlib.h>
#include "rt.h"
#include "libft.h"
#include "ft_printf.h"

t_mlx_img	*create_mlx_img_from_data(t_mlx *mlx, void *data,
	int width, int height)
{
	t_mlx_img *img;

	if (!mlx)
		exit_message("create_mlx_img_from_data: mlx is null!");
	if (!(img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
		exit_message("create_mlx_img_from_data: failed to malloc t_mlx_img!");
	img->width = width;
	img->height = height;
	img->img = data;
	if (!(img->d_addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian)))
		exit_message("create_mlx_img_from_data: mlx_get_data_addr failed!");
	img->bpp /= 8;
	return (img);
}

t_mlx_img	*create_mlx_img(t_mlx *mlx, int width, int height)
{
	t_mlx_img *img;

	if (!mlx)
		return (NULL);
	if (!(img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
		exit_message("create_mlx_image failed!");
	img->width = width;
	img->height = height;
	if (!(img->img = mlx_new_image(mlx->mlx_ptr,
									img->width, img->height)))
		exit_message("mlx_new_image failed!");
	if (!(img->d_addr = mlx_get_data_addr(img->img, &img->bpp,
										&img->size_line, &img->endian)))
		exit_message("mlx_get_data_addr failed!");
	img->bpp /= 8;
	return (img);
}

void		destroy_mlx_img(t_mlx *mlx, t_mlx_img *mlx_img)
{
	if (!mlx || !mlx_img)
	{
		ft_putendl("destroy_mlx_img: mlx or mlx_img was null!");
		return ;
	}
	mlx_destroy_image(mlx->mlx_ptr, mlx_img->img);
	free(mlx_img);
	mlx_img = NULL;
}

void		put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	*(int*)(img->d_addr + (((y * img->width) + x) * img->bpp)) = c;
}

int			get_pixel_mlx_img(t_mlx_img *img, int x, int y)
{
	int c;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (-1);
	c = *(int*)(img->d_addr + (((y * img->width) + x) * img->bpp));
	return (c);
}

t_mlx_img	*load_xpm_to_mlx_img(t_mlx *mlx, char *file)
{
	t_mlx_img	*mlx_img;
	t_vec2i		size;
	void		*img_data;

	if (!(img_data = mlx_xpm_file_to_image(
			mlx->mlx_ptr, file, &size.x, &size.y)))
		exit_message("xpm_loader: failed to load xpm file!");
	if (!(mlx_img = create_mlx_img_from_data(mlx, img_data, size.x, size.y)))
		exit_message("xpm_loader: create_mlx_img_from_data failed!");
	ft_printf("finished loading: %s\n", file);
	return (mlx_img);
}
