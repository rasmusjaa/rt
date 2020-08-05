/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inv_lerp_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:58:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/16 11:58:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_inv_lerp_d(double value, double a, double b)
{
	if ((a == b) || (value <= a))
		return (0.0f);
	if (value >= b)
		return (1.0f);
	return (((value - a) * 1.0f) / (b - a));
}
