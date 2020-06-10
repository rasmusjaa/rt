/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:37:20 by wkorande          #+#    #+#             */
/*   Updated: 2020/02/06 11:46:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifndef __linux__

#  define KEY_ESC		53
#  define KEY_NUM_MULT	67
#  define KEY_NUM_DIV	75
#  define KEY_NUM_PLUS	69
#  define KEY_NUM_MINUS	78
#  define KEY_NUM_ENTER	76
#  define KEY_NUM_0		82
#  define KEY_NUM_1		83
#  define KEY_NUM_2		84
#  define KEY_NUM_3		85
#  define KEY_NUM_4		86
#  define KEY_NUM_5		87
#  define KEY_NUM_6		88
#  define KEY_NUM_7		89
#  define KEY_NUM_8		91
#  define KEY_NUM_9		92
#  define KEY_NUM_LEFT	86
#  define KEY_NUM_RIGHT	88
#  define KEY_NUM_UP	91
#  define KEY_NUM_DOWN	84
#  define KEY_UP		126
#  define KEY_DOWN		125
#  define KEY_LEFT		123
#  define KEY_RIGHT		124
#  define KEY_SPACE		49
#  define KEY_1			18
#  define KEY_2			19
#  define KEY_3			20
#  define KEY_I			34

# else

#  define KEY_ESC		65307
#  define KEY_NUM_MULT	65450
#  define KEY_NUM_DIV	65455
#  define KEY_NUM_PLUS	65451
#  define KEY_NUM_MINUS	65453
#  define KEY_NUM_ENTER	65421
#  define KEY_NUM_0		65438
#  define KEY_NUM_1		65436
#  define KEY_NUM_2		65433
#  define KEY_NUM_3		65435
#  define KEY_NUM_4		65430
#  define KEY_NUM_5		65437
#  define KEY_NUM_6		65432
#  define KEY_NUM_7		65429
#  define KEY_NUM_8		65431
#  define KEY_NUM_9		65434
#  define KEY_NUM_LEFT	65430
#  define KEY_NUM_RIGHT	65432
#  define KEY_NUM_UP	65431
#  define KEY_NUM_DOWN	65433
#  define KEY_UP		65362
#  define KEY_DOWN		65364
#  define KEY_LEFT		65361
#  define KEY_RIGHT		65363
#  define KEY_SPACE		32
#  define KEY_1			49
#  define KEY_2			50
#  define KEY_3			51
#  define KEY_I			105

# endif

#endif
