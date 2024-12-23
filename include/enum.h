/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:42:39 by we                #+#    #+#             */
/*   Updated: 2024/12/23 09:55:05 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum e_keycode
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_MINUS = 45,
	KEY_PLUS = 61,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363
};

enum e_event
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	BUTTON_PRESS = 4,
	BUTTON_RELEASE = 5,
	MOTION_NOTIFY = 6,
	CREATE_NOTIFY = 16,
	DESTROY_NOTIFY = 17,
	RESIZE_REQUEST = 25,
	GENERIC_EVENT = 35,
	LAST_EVENT = 36
};

enum e_mask
{
	NOT_EVENT_MASK = 0L,
	KEY_PRESS_MASK = 1L<<0,
	KEY_RELEASE_MASK = 1L<<1,
	BUTTON_PRESS_MASK = 1L<<2,
	BUTTON_RELEASE_MASK = 1L<<3,
	POINTER_MOTION_MASK = 1L<<6,
};

#endif
