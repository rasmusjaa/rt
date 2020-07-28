#include <fcntl.h>
#include "image_save_load.h"

static int		image_allocate(t_image_data *image, char *line)
{
	int x;
	int y;
	int i;

	if (!line)
		return (-1);
	x = ft_atoi(line);
	y = ft_atoi(ft_strchr(line, ' '));
	if (x == 0 || y == 0)
		return (-1);
	if (!(image->pixels = (t_rgba8*)malloc(sizeof(t_rgba8) * x * y))) 
		return (-1);
	image->width = x;
	image->height = y;
	i = 0;
	while (i < x * y)
	{
		image->pixels[i] = rgba8_init();
		i++;
	}
	return (0);
}

static int		data_from_line(t_image_data *image, char *line, int *gap, int *i)
{
	int data;
	int j = 0;
	
	while (*line)
	{
		*gap %= 3;
		data = ft_atoi(line);
		if (*gap == 0)
			image->pixels[*i].r = data;
		if (*gap == 1)
			image->pixels[*i].g = data;
		if (*gap == 2)
			image->pixels[*i].b = data;
		while (*line != ' ' && *line)
			line++;
		if (*line == ' ')
			line++;
		if (*gap >= 2)
			*i += 1;
		*gap += 1;
		j++;
	}
	
	return (0);
}

static int		read_pixels(t_image_data *image, int fd)
{
	int gap;
	int i;
	int data;
	char *line;

	i = 0;
	gap = 0;
	ft_get_next_line(fd, &line);
	if (!line)
		return (-1);
	image->color_range = ft_atoi(line);
	free(line);
	while (ft_get_next_line(fd, &line) > 0)
	{
		data_from_line(image, line, &gap, &i);
		free(line);
	}
	return (0);
}

int bin_read_pixels(t_image_data *image, int fd)
{
	int data[3];
	int gap;
	int i;
	int ret;

	i = 0;
	gap = 0;
	read(fd, &data, 1);
	while ((ret = read(fd, data, 1)) > 0) 
	{
		gap = gap % 3;
		if (gap == 0)
			image->pixels[i].r = data[0];
		if (gap == 1)
			image->pixels[i].g = data[0];
		if (gap == 2)
			image->pixels[i].b = data[0];
		gap += ret;
		if (gap == 3)
			i++;
	}
	return (ret);
}

static int	process_file(t_image_data *image, int fd, char *filename)
{
	char *line;
	int ret;
	int binary;

	ret = ft_get_next_line(fd, &line);
	binary = -1;
	if (ft_strcmp(line, "P6") == 0)
		binary = 1;
	else if (ft_strcmp(line, "P3") == 0)
		binary = 0;
	free(line);
	if (binary == -1)
		return (-1);
	while ((ret = ft_get_next_line(fd, &line)) > 0)
	{
		if (line[0] != '#' || line[0] == '\n')
			break ;
		free(line);
	}
	if (ret <= 0)
		return (-1);
	image_allocate(image, line);
	free(line);
	return (binary == 0 ? read_pixels(image, fd) :
		bin_read_pixels(image, fd));
}

t_image_data	*img_load_ppm(char *filename)
{
	int fd;
	char *filext;
	t_image_data *image;

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
	image = image_data_init();
	if (process_file(image, fd, filename) == -1)
		return (NULL);
	image->file_path = ft_strdup(filename);
	close(fd);
	return (image);
}
