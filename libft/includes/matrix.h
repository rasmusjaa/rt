/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 10:46:30 by wkorande          #+#    #+#             */
/*   Updated: 2020/02/06 13:48:25 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct	s_mat4x4
{
	double		m[4][4];
}				t_mat4x4;

typedef struct	s_mat3x3
{
	double		m[3][3];
}				t_mat3x3;

t_mat4x4		ft_ident_mat4(void);
t_mat4x4		ft_mul_mat4_mat4(t_mat4x4 a, t_mat4x4 b);
t_vec3			ft_mul_vec3_mat4(t_vec3 in, t_mat4x4 m);
t_vec3			ft_mul_dir_vec3_mat4(t_vec3 in, t_mat4x4 m);
t_mat4x4		ft_create_trans_mat4(t_vec3 translation);
t_mat4x4		ft_create_rotx_mat4(float angle);
t_mat4x4		ft_create_roty_mat4(float angle);
t_mat4x4		ft_create_rotz_mat4(float angle);
t_mat4x4		ft_create_rot_mat4(t_vec3 deg_angle);
t_mat4x4		ft_create_scale_mat4(t_vec3 scale);
t_mat4x4		ft_trs_mat4(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4x4		ft_lookat_mat4(t_vec3 from, t_vec3 to, t_vec3 world_up);
t_mat4x4		ft_transpose_mat4(t_mat4x4 m);
void			ft_print_mat4(t_mat4x4 m);

#endif
