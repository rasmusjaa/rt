/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 22:49:46 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/09 23:31:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include "vector.h"
#include "rt.h"

void			draw_line(t_mlx *mlx, t_vec2i p0, t_vec2i p1, int color);
t_vec2i world_to_screen_point(t_camera *camera, t_vec3 world_point, t_vec2i window_size);
void	draw_model_bounds(t_mlx *mlx, t_scene *scene);
void	print_vec3(char *s, t_vec3 v);
void	print_rgba(char *s, t_rgba c);
#endif