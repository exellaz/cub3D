/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/01/03 18:56:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"

int	quit(int keycode, t_mlx *m)
{
	(void)keycode;
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_mlx *m)
{
	if (keycode == KEY_ESC)
		quit(keycode, m);
	if (keycode == KEY_W)
		m->player->y -= 5;
	if (keycode == KEY_S)
		m->player->y += 5;
	if (keycode == KEY_A)
		m->player->x -= 5;
	if (keycode == KEY_D)
		m->player->x += 5;
	return (0);
}
