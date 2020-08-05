/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp_rgba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:10:48 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/22 16:24:59 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

t_rgba	ft_lerp_rgba(t_rgba c1, t_rgba c2, double t)
{
	t_rgba color;

	color.r = ft_lerp_d(c1.r, c2.r, t);
	color.g = ft_lerp_d(c1.g, c2.g, t);
	color.b = ft_lerp_d(c1.b, c2.b, t);
	color.a = ft_lerp_d(c1.a, c2.a, t);
	color = ft_clamp_rgba(color);
	return (color);
}
