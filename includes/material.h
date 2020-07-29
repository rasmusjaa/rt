/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:09:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/29 13:49:39 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "rt.h"
# include "color.h"

# define DEFAULT_MATERIAL_ID SIZE_MAX

struct s_texture;

typedef struct		s_material
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
}					t_material;

typedef struct s_scene t_scene;

t_material			new_material(size_t id, t_rgba diffuse, struct s_texture *texture);

t_material			*get_material_by_id(t_scene *scene, size_t id);
struct s_texture			*get_texture_by_id(t_scene *scene, size_t id);

#endif
