/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <willehard@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:27:02 by wkorande          #+#    #+#             */
/*   Updated: 2020/07/03 17:42:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh	*obj_load(const char *filename);

int main(void)
{
	obj_load("test.obj");
	return (0);
}
