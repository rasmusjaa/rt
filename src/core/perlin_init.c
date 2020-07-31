/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:08:07 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/30 22:40:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"

void  delete_gradient_vectors(unsigned char  ***g)
{
	int i;
	int j;

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

static unsigned char  ***create_gradient_vectors(void)
{
	unsigned char	***g;
	int				i;
	int				j;

	j = 0;
	g = malloc(sizeof(char**)*GRAD_MAX);
	while (j < GRAD_MAX)
	{
		if (!(g[j] = malloc(sizeof(char*) *GRAD_MAX)))
            return (NULL);
		i = 0;
		while(i < GRAD_MAX)
		{
			if (!(g[j][i] = malloc(sizeof(char) * 2)))
                return (NULL);
			g[j][i][0] = rand() % 255;
			g[j][i][1] = rand() % 255;
			i++;
		}
		j++;
	}
	return (g);
}


int		perlin_init(t_rt *rt, t_texture *texture)
{
    if (rt->grad_vectors == NULL)
        rt->grad_vectors = create_gradient_vectors();
    if (!rt->grad_vectors)
        return (-1);
    texture->grad_vectors = rt->grad_vectors;
    return (0);
}
