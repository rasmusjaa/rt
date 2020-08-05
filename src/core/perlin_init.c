/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:08:07 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/05 13:35:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"

static t_perlin_data	*create_perlin_data(void)
{
	t_perlin_data	*perlin;
	int				i;
	int				other;

	if (!(perlin = (t_perlin_data*)malloc(sizeof(t_perlin_data))))
		return (NULL);
	i = 0;
	while (i < 256)
	{
		other = rand() % (i + 1);
		if (i > other)
			perlin->perm[i] = perlin->perm[other];
		perlin->perm[other] = i;
		perlin->grads_x[i] = cos(2.0 * M_PI * (double)i / 256.0);
		perlin->grads_y[i] = sin(2.0 * M_PI * (double)i / 256.0);
		i++;
	}
	return (perlin);
}

int						perlin_init(t_rt *rt, t_texture *texture)
{
	if (rt->perlin_data == NULL)
		rt->perlin_data = create_perlin_data();
	if (!rt->perlin_data)
		return (-1);
	texture->perlin_data = rt->perlin_data;
	return (0);
}
