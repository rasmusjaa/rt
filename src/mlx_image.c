/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:00:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/06/16 16:11:01 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

static void panic(char *error)
{
	ft_putendl(error);
	exit(EXIT_FAILURE);
}

t_mlx_img	*create_mlx_img(t_mlx *mlx, int width, int height)
{
	t_mlx_img *img;

	if (!mlx)
		return (NULL);
	if (!(img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
		panic("create_mlx_image failed!");
	img->width = width;
	img->height = height;
	if (!(img->img = mlx_new_image(mlx->mlx_ptr,
									img->width, img->height)))
		panic("mlx_new_image failed!");
	if (!(img->d_addr = mlx_get_data_addr(img->img, &img->bpp,
										&img->size_line, &img->endian)))
		panic("mlx_get_data_addr failed!");
	img->bpp /= 8;
	return (img);
}

void	destroy_mlx_img(t_mlx *mlx, t_mlx_img *mlx_img)
{
	if (!mlx || !mlx_img)
	{
		ft_putendl("Failed to destroy mlx_img!");
		return ;
	}
	mlx_destroy_image(mlx->mlx_ptr, mlx_img->img);
	free(mlx_img);
}

void		put_pixel_mlx_img(t_mlx_img *img, int x, int y, int c)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	*(int*)(img->d_addr + (((y * img->width) + x) * img->bpp)) = c;
}
