/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_range.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:40:55 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 13:43:52 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clamp_range(double v, double min, double max)
{
	if (v < min)
		return (min);
	else if (v > max)
		return (max);
	return (v);
}
