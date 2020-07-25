/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 11:31:29 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/25 12:08:38 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx_image.h"
#include "mlx.h"
#include "rt.h"
#include "ft_printf.h"

t_mlx_img	*load_xmp_to_mlx_img(t_mlx *mlx, char *file)
{
	t_mlx_img	*mlx_img;
	t_vec2i 	size;
	void		*img_data;
	
	if (!(img_data = mlx_xpm_file_to_image(mlx->mlx_ptr, file, &size.x, &size.y)))
		exit_message("xpm_loader: failed to load xpm file!");
	
	if (!(mlx_img = create_mlx_img_from_data(mlx, img_data, size.x, size.y)))
		exit_message("xpm_loader: create_mlx_img_from_data failed!");
	return (mlx_img);
}
