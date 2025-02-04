/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:42:39 by we                #+#    #+#             */
/*   Updated: 2025/01/28 15:09:12 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum e_keycode
{
	KEY_ESC = 0,
	KEY_W = 1,
	KEY_A = 2,
	KEY_S = 3,
	KEY_D = 4,
	KEY_M = 5,
	KEY_LEFT = 7,
	KEY_RIGHT = 8
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
