/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rgba.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:17:38 by wkorande          #+#    #+#             */
/*   Updated: 2020/02/03 18:18:02 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

t_rgba	ft_parse_rgba(char *line)
{
	t_rgba	c;
	char	*token;

	line = ft_strstr(line, " ");
	token = ft_strtok(line, " ");
	c.r = ft_strtod(token);
	token = ft_strtok(NULL, " ");
	c.g = ft_strtod(token);
	token = ft_strtok(NULL, " ");
	c.b = ft_strtod(token);
	c.a = 1.0;
	return (c);
}
