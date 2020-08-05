/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:09:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/08/05 13:15:47 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "rt.h"
# include "color.h"

# define DEFAULT_MATERIAL_ID SIZE_MAX

struct s_texture;
struct s_scene;

typedef struct			s_material
{
	size_t				id;
	t_rgba				diffuse;
	double				shininess;
	double				specular;
	size_t				texture_id;
	struct s_texture	*texture;
	double				refra_index;
	double				reflection;
	double				opacity;
	double				u_scale;
	double				v_scale;
	double				explode;
	size_t				normal_tex_id;
	size_t				bump_tex_id;
	double				normal_mult;
	double				bump_mult;
}						t_material;

t_material				new_material(size_t id, t_rgba diffuse,
							struct s_texture *texture);
t_material				*get_material_by_id(struct s_scene *scene, size_t id);
struct s_texture		*get_texture_by_id(struct s_scene *scene, size_t id);

#endif
