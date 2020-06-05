/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:59:56 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/05 16:18:33 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_rt()
{
	t_rt	*rt;

	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		exit_message("Failed to malloc rt!");
	num_scenes = 0;
}

int		main(int ac, char **av)
{
	t_rt	*rt;
	int		i;

	rt = init_rt();
	i = 0;
	if (ac == 1)
		exit_message("Usage:")
	else
	{
		while (i < ac - 1)
		{
			rt->scenes[i] = read_scene(av[i + 1], rt);
			i++;
		}
	}

	return (0);
}
