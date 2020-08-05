/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ppm2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:56:08 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/03 17:35:45 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "ft_get_next_line.h"
#include "libft.h"

static int	data_from_line(char *data, char *line, int *gap, int *i)
{
	int file_data;
	int j;

	j = 0;
	while (*line)
	{
		*gap %= 3;
		file_data = ft_atoi(line);
		if (*gap == 0)
			data[*i + 0] = file_data;
		if (*gap == 1)
			data[*i + 1] = file_data;
		if (*gap == 2)
			data[*i + 2] = file_data;
		while (*line != ' ' && *line)
			line++;
		if (*line == ' ')
			line++;
		if (*gap >= 2)
			*i += 4;
		*gap += 1;
		j++;
	}
	return (0);
}

static int	check_file_color_range(int fd)
{
	char line[5];

	read(fd, line, 4);
	line[4] = '\0';
	if (ft_strcmp(line, "255\n") != 0)
		return (-1);
	return (0);
}

int			ppm_read_pixels(int fd, char *data, int *width, int *height)
{
	int		gap;
	int		i;
	int		ret;
	char	*line;

	i = 0;
	gap = 0;
	if (!data)
		return (-1);
	ft_get_next_line(fd, &line);
	if (!line || ft_strcmp(line, "255") != 0)
		return (-1);
	free(line);
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		data_from_line(data, line, &gap, &i);
		free(line);
		if (i >= *width * *height * 4)
			break ;
	}
	return (ret);
}

int			ppm_bin_read_pixels(int fd, char *data, int *width, int *height)
{
	int file_data[3];
	int gap;
	int i;
	int ret;

	i = 0;
	gap = 0;
	if (!data)
		return (-1);
	if (check_file_color_range(fd) == -1)
		return (-1);
	while ((ret = read(fd, file_data, 1)) > 0 && i < *width * *height * 4)
	{
		gap = gap % 3;
		if (gap == 0)
			data[i + 0] = file_data[0];
		if (gap == 1)
			data[i + 1] = file_data[0];
		if (gap == 2)
			data[i + 2] = file_data[0];
		gap += ret;
		if (gap == 3)
			i += 4;
	}
	return (ret);
}
