/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_asppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sluhtala <sluhtala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 13:37:27 by sluhtala          #+#    #+#             */
/*   Updated: 2020/06/09 15:36:32 by sluhtala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image_save_load.h"
#include <fcntl.h>
#include <sys/types.h>

void	write_header(int file, int w, int h)
{
	char *text;

	write(file, "P3\n", 3);
	text = ft_itoa(w);
	write(file, text, ft_strlen(text));
	write(file, " ", 1);
	free(text);
	text = ft_itoa(h);
	write(file, text, ft_strlen(text));
	free(text);
	write(file, "\n", 1);
	write(file, "255\n", 4);
}

char	*get_line(unsigned char *img, int x, int y, int stride)
{
	char *t;
	char *temp;
	char *line;

	t = ft_itoa(img[4 * (y * stride + x) + 0]);
	line = ft_strjoin(t, " ");
	free(t);
	t = ft_itoa(img[4 * (y * stride + x) + 1]);
	temp = ft_strjoin(line, t);
	free(line);
	free(t);
	line = ft_strjoin(temp, " ");
	free(temp);
	t = ft_itoa(img[4 * (y * stride + x) + 2]);
	temp = ft_strjoin(line, t);
	free(line);
	free(t);
	line = ft_strjoin(temp, " ");
	free(temp);
	return (line);
}

void	write_data(int file, unsigned char *img, int width, int height)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			line = get_line(img, x, y, width);
			write(file, line, ft_strlen(line));
			free(line);
			if (x != 0 && x % 5 == 0)
			{
				write(file, "\n", 1);
			}
			x++;
		}
		write(file, "\n", 1);
		y++;
	}
	write(file, "\n", 1);
}

void	img_to_ppm(unsigned char *img, char *file_name, int width, int height)
{
	int file;

	ft_printf("Saving to image.ppm...\n");
	file = open(file_name, O_RDWR | O_CREAT, 777);
	if (file == -1)
	{
		ft_printf("Error saving image.\n");
		return ;
	}
	write_header(file, width, height);
	write_data(file, img, data);
	ft_printf("Image saved\n");
	close(file);
}
