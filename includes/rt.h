/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 01:19:59 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/06/04 15:23:43 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define N_OBJECTS 7

# define MIN_COORD -100
# define MAX_COORD 100

# include "color.h"
# include "ft_get_next_line.h"
# include "ft_hashtable.h"
# include "ft_printf.h"
# include "ft_queue.h"
# include "ft_stack.h"
# include "libft.h"
# include "matrix.h"
# include "vector.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

typedef void		(*t_object_func)(char *line);

typedef struct		s_objects
{
	char			object[5];
	t_object_func	func;
}					t_objects;

double double_clamp_0(double nb, double min, double max);
double ft_double_clamp(double nb, double min, double max);
void exit_message(char *str);
void read_scene(char *str);

#endif
