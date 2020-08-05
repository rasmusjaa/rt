/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:37:45 by wkorande          #+#    #+#             */
/*   Updated: 2019/10/30 10:18:45 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

static int	ft_contains_char(char *str, char c)
{
	while (*(str++) != '\0')
		if (*str == c)
			return (1);
	return (0);
}

static char	*ft_free_and_assign(char *descs, char *tmp)
{
	free(descs);
	descs = tmp;
	return (descs);
}

static int	ft_serve_line(int fd, char **descs, char **line, int bytes)
{
	char	*tmp;
	int		len;

	if ((bytes < 0))
		return (-1);
	if ((bytes == 0 && descs[fd] == NULL) || descs[fd][0] == '\0')
		return (0);
	len = 0;
	while (descs[fd][len] != '\n' && descs[fd][len] != '\0')
		len++;
	if (descs[fd][len] == '\n')
	{
		if (!(*line = ft_strsub(descs[fd], 0, len)))
			return (-1);
		if (!(tmp = ft_strdup(descs[fd] + len + 1)))
			return (-1);
		descs[fd] = ft_free_and_assign(descs[fd], tmp);
	}
	else if (descs[fd][len] == '\0')
	{
		*line = ft_strdup(descs[fd]);
		free(descs[fd]);
		descs[fd] = NULL;
	}
	return (1);
}

int			ft_get_next_line(const int fd, char **line)
{
	static char	*descs[MAX_FD];
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	int			bytes;

	if (fd < 0 || !line)
		return (-1);
	while ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		if (descs[fd] == NULL)
		{
			if (!(descs[fd] = ft_strdup(buffer)))
				return (-1);
		}
		else
		{
			if (!(tmp = ft_strjoin(descs[fd], buffer)))
				return (-1);
			descs[fd] = ft_free_and_assign(descs[fd], tmp);
		}
		if (ft_contains_char(descs[fd], '\n'))
			break ;
	}
	return (ft_serve_line(fd, descs, line, bytes));
}
