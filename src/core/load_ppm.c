/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:56:08 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/03 16:56:12 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_image.h"
#include "ft_get_next_line.h"
#include "libft.h"

static char		*image_allocate(char *line, int *width, int *height)
{
	int		i;
	char	*data;

	if (!line)
		return (NULL);
	*width = ft_atoi(line);
	*height = ft_atoi(ft_strchr(line, ' '));
	if (*width == 0 || *height == 0)
		return (NULL);
	if (!(data = (char*)malloc(sizeof(char) * *height * *width * 4)))
		return (NULL);
	i = 0;
	while (i < *width * *height)
	{
		data[i * 4 + 0] = 0;
		data[i * 4 + 1] = 0;
		data[i * 4 + 2] = 0;
		data[i * 4 + 3] = 1;
		i++;
	}
	return (data);
}

static int		check_if_binary(int fd)
{
	int		binary;
	char	*line;

	binary = -1;
	if (ft_get_next_line(fd, &line) <= 0)
		return (-1);
	if (line && ft_strcmp(line, "P6") == 0)
		binary = 1;
	else if (line && ft_strcmp(line, "P3") == 0)
		binary = 0;
	free(line);
	return (binary);
}

static int		read_comments(int fd, char **line)
{
	int ret;

	ret = -1;
	while ((ret = ft_get_next_line(fd, line)) > 0)
	{
		if (line[0][0] != '#' || line[0][0] == '\n')
			break ;
		free(*line);
	}
	return (ret);
}

static char		*process_file(int fd, int *width, int *height)
{
	char	*line;
	int		ret;
	int		binary;
	char	*data;

	if ((binary = check_if_binary(fd)) == -1)
		return (NULL);
	if (read_comments(fd, &line) == -1)
		return (NULL);
	data = image_allocate(line, width, height);
	free(line);
	if (binary == 0)
		ret = ppm_read_pixels(fd, data, width, height);
	else
		ret = ppm_bin_read_pixels(fd, data, width, height);
	if (ret == -1)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

char			*img_load_ppm(char *filename, int *width, int *height)
{
	int		fd;
	char	*filext;
	char	*data;

	filext = ft_strrchr(filename, '.');
	if (!filext || ft_strcmp(filext, ".ppm"))
	{
		ft_putendl("Error not .ppm file");
		return (NULL);
	}
	if ((fd = open(filename, O_RDONLY)) == -1 || read(fd, NULL, 0) == -1)
	{
		ft_putendl("Error opening file");
		return (NULL);
	}
	data = NULL;
	if ((data = process_file(fd, width, height)) == NULL)
	{
		ft_putendl("error img_load_ppm");
		return (NULL);
	}
	close(fd);
	return (data);
}
