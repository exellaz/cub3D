/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/01/06 13:13:45 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"
#include "math.h"

int	quit(int keycode, t_mlx *m)
{
	(void)keycode;
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_mlx *m)
{
	t_player *player = m->player;
	int	speed = 5;
	float	angle_speed = 0.1;
	float	cos_angle = cos(player->angle);
	float	sin_angle = sin(player->angle);

	if (keycode == KEY_ESC)
		quit(keycode, m);
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (keycode == KEY_W)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (keycode == KEY_S)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (keycode == KEY_A)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (keycode == KEY_D)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (keycode == KEY_LEFT)
	{
		player->angle -= angle_speed;
	}
	if (keycode == KEY_RIGHT)
	{
		player->angle += angle_speed;
	}
	return (0);
}
