/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_rgba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:08:15 by wkorande          #+#    #+#             */
/*   Updated: 2020/02/05 17:23:11 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

t_rgba	ft_clamp_rgba(t_rgba c)
{
	c.r = ft_clamp_d(c.r, 0.0, 1.0);
	c.g = ft_clamp_d(c.g, 0.0, 1.0);
	c.b = ft_clamp_d(c.b, 0.0, 1.0);
	c.a = ft_clamp_d(c.a, 0.0, 1.0);
	return (c);
}
