/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:23:19 by wkorande          #+#    #+#             */
/*   Updated: 2020/08/03 15:28:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDS_H
# define BOUNDS_H

# include "vector.h"
// # include "raycast.h"

# define MAX_BOUNDS 10000
# define MIN_BOUNDS -10000

struct s_shape;
struct s_ray;

typedef struct	s_bounds
{
	int			active;
	t_vec3		min;
	t_vec3		max;
}				t_bounds;

int				inside_bounds(t_bounds object_bounds, t_bounds bounds);
int				point_inside_bounds(t_vec3 p, struct s_shape *shape);
int				intersects_bounds(struct s_ray *ray, t_bounds *b, int debug);

#endif
