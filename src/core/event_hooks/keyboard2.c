/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:37:55 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/08/03 11:41:53 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "object.h"

void	rotate_camera(int key, t_camera *c)
{
	if (key == KEY_NUM_4)
		c->rotation.y += 10.0;
	else if (key == KEY_NUM_6)
		c->rotation.y -= 10.0;
	else if (key == KEY_NUM_8)
		c->rotation.x -= 10.0;
	else if (key == KEY_NUM_2)
		c->rotation.x += 10.0;
}
