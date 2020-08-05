/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:08:07 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/03 12:24:15 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"
/*
void					delete_gradient_vectors(unsigned char ***g)
{
	int	i;
	int	j;

	j = 0;
	if (!g)
		return ;
	while (j < GRAD_MAX)
	{
		i = 0;
		while (i < GRAD_MAX)
		{
			free(g[j][i]);
			i++;
		}
		free(g[j]);
		j++;
	}
	free(g);
}

static unsigned char	***create_gradient_vectors(void)
{
	unsigned char	***g;
	int				i;
	int				j;

	j = 0;
	if (!(g = malloc(sizeof(char**) * GRAD_MAX)))
		exit_message("Failed to malloc perlin vectors!");
	while (j < GRAD_MAX)
	{
		if (!(g[j] = malloc(sizeof(char*) * GRAD_MAX)))
			exit_message("Failed to malloc perlin vectors!");
		i = 0;
		while (i < GRAD_MAX)
		{
			if (!(g[j][i] = malloc(sizeof(char) * 2)))
				exit_message("Failed to malloc perlin vectors!");
			g[j][i][0] = rand() % 255;
			g[j][i][1] = rand() % 255;
			i++;
		}
		j++;
	}
	return (g);
}
*/

static t_perlin_data	*create_perlin_data(void)
{
	t_perlin_data *perlin;
	int i;
	int other;

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
