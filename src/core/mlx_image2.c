/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 16:00:45 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 12:28:44 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include <stdlib.h>
#include "rt.h"
#include "libft.h"
#include "ft_printf.h"

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

t_mlx_img	*load_ppm_to_mlx_img(char *file)
{
	t_mlx_img		*mlx_img;
	t_vec2i			size;
	unsigned char	*data;

	if (!(mlx_img = (t_mlx_img*)malloc(sizeof(t_mlx_img))))
		exit_message("create_mlx_img_from_data: failed to malloc t_mlx_img!");
	if (!(data = (unsigned char*)img_load_ppm(
		file, &size.x, &size.y)))
		exit_message("ppm_loader: failed to load ppm file!");
	mlx_img->d_addr = (void*)data;
	mlx_img->bpp = 4;
	mlx_img->img = NULL;
	mlx_img->width = size.x;
	mlx_img->height = size.y;
	ft_printf("finished loading: %s\n", file);
	return (mlx_img);
}

t_mlx_img	*load_file_to_mlx_img(t_mlx *mlx, char *file)
{
	t_mlx_img	*mlx_img;
	char		*suffix;

	mlx_img = NULL;
	suffix = ft_strrchr(file, '.');
	if (!suffix || (ft_strcmp(suffix, ".ppm") != 0 &&
		ft_strcmp(suffix, ".xpm") != 0))
	{
		ft_printf("invalid image file type \"%s\"\n", file);
		return (NULL);
	}
	if (ft_strcmp(suffix, ".xpm") == 0)
		mlx_img = load_xpm_to_mlx_img(mlx, file);
	else if (ft_strcmp(suffix, ".ppm") == 0)
		mlx_img = load_ppm_to_mlx_img(file);
	return (mlx_img);
}
