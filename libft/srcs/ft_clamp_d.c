/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:58:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/18 12:58:43 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clamp_d(double d, double min, double max)
{
	if (d < min)
		d = min;
	if (d > max)
		d = max;
	return (d);
}
