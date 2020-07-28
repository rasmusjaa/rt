/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:09:34 by sluhtala          #+#    #+#             */
/*   Updated: 2020/07/28 18:44:29 by rjaakonm         ###   ########.fr       */
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
	int					texture_id;
	struct s_texture	*texture;
	double				refra_index;
	double				reflection;
	double				opacity;
	double				u_scale;
	double				v_scale;
	double				explode;
}					t_material;

typedef struct s_scene t_scene;

t_material			new_material(size_t id, t_rgba diffuse, struct s_texture *texture);

//void				allocate_textures(t_scene *scene, size_t amount);
//void				allocate_materials(t_scene *scene, size_t amount);


t_material			*get_material_by_id(t_scene *scene, size_t id);
struct s_texture			*get_texture_by_id(t_scene *scene, size_t id);

// t_vec2		cylinder_uv(t_vec3 point, double max, double min);
// t_vec2		sphere_uv(t_vec3 point);
// t_vec2		plane_uv(t_vec3 point);


#endif
