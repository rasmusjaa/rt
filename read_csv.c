/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_csv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:08:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/05 00:02:21 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	double_clamp_0(double nb, double min, double max)
{
	if (nb < min)
		return (0);
	if (nb > max)
		return (0);
	return (nb);
}

double	ft_double_clamp(double nb, double min, double max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

double	get_field(int field, char *line)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == ';')
			counter++;
		if (counter == field)
		{
			return(ft_strtod(&line[i + 1]));
		}
		i++;
	}
	return 0;
}

void	check_camera_fields(char *line)
{
	ft_printf("field %d = %f\n", 1, ft_double_clamp(get_field(1, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 2, ft_double_clamp(get_field(2, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 3, ft_double_clamp(get_field(3, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 4, ft_double_clamp(get_field(4, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 5, ft_double_clamp(get_field(5, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 6, ft_double_clamp(get_field(6, line), MIN_COORD, MAX_COORD));
	ft_printf("field %d = %f\n", 40, ft_double_clamp(get_field(40, line), MIN_COORD, MAX_COORD));
}

t_objects g_objects[N_OBJECTS] =
{
	{"came", check_camera_fields},
	{"scen", check_camera_fields},
	{"sphe", check_camera_fields},
	{"plan", check_camera_fields},
	{"cyli", check_camera_fields},
	{"cone", check_camera_fields},
	{"spot", check_camera_fields}
};

void exit_message(char *str)
{
	ft_putendl(str);
	exit(1);
}

int			handle_line(char *str)
{
	int i;

	i = 0;
	while (i < N_OBJECTS)
	{
		if (ft_strncmp(str, g_objects[i].object, 4) == 0)
		{
			ft_printf("match line %s\n", str);
			g_objects[i].func(str);
		}
		i++;
	}
	i = 0;
	return (0);
}

void		read_scene(char *str)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit_message("Invalid file");
	while (ft_get_next_line(fd, &line) > 0)
	{
		handle_line(line);
		free(line);
	}
}
