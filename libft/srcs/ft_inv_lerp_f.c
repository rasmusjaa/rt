/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inv_lerp_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:36:17 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/15 16:36:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_inv_lerp_f(float value, float a, float b)
{
	if ((a == b) || (value <= a))
		return (0.0f);
	if (value >= b)
		return (1.0f);
	return (((value - a) * 1.0f) / (b - a));
}
