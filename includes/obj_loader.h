/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:20:00 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/23 14:55:10 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_LOADER_H
# define OBJ_LOADER_H

# include "shape.h"
# include "mesh.h"

t_mesh			*obj_load(const char *filename, t_shape shape);

#endif
