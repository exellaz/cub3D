/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/01/10 19:48:37 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"
#include "math.h"
#include "stdio.h"

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
	float	speed = 0.1;
	float	rot_speed = 0.1;

	if (keycode == KEY_ESC)
		quit(keycode, m);
	if (keycode == KEY_W)
	{
		player->pos_x += player->dir_x * speed;
		player->pos_y += player->dir_y * speed;
	}
	if (keycode == KEY_S)
	{
		player->pos_x -= player->dir_x * speed;
		player->pos_y -= player->dir_y * speed;
	}
	if (keycode == KEY_A)
	{
		player->pos_x -= player->dir_y * speed;
		player->pos_y += player->dir_x * speed;
	}
	if (keycode == KEY_D)
	{
		player->pos_x += player->dir_y * speed;
		player->pos_y -= player->dir_x * speed;
	}
	if (keycode == KEY_LEFT)
	{
		float	old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
	}
	if (keycode == KEY_RIGHT)
	{
		float	old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
	}
	return (0);
}
