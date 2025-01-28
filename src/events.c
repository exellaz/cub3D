/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/01/28 12:08:46 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"
#include "math.h"
#include "stdio.h"
#include <X11/Xlib.h>

int	quit(int keycode, t_vars *m)
{
	(void)keycode;
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

int key_press_hook(int keycode, t_vars *m)
{
	// t_player *player = m->player;
	// float	speed = 0.1;
	// float	rot_speed = 0.1;
	// float	speed = m->fps->frame_time * 5.0;
	// float	rot_speed = m->fps->frame_time * 3.0;

	if (keycode == KEY_ESC)
		quit(keycode, m);
	if (keycode == KEY_W)
	{
		m->keys[keycode] = true;
		// player->pos_x += player->dir_x * speed;
		// player->pos_y += player->dir_y * speed;
	}
	if (keycode == KEY_S)
	{
		m->keys[keycode] = true;
		// player->pos_x -= player->dir_x * speed;
		// player->pos_y -= player->dir_y * speed;
	}
	if (keycode == KEY_A)
	{
		m->keys[keycode] = true;
		// player->pos_x -= player->dir_y * speed;
		// player->pos_y += player->dir_x * speed;
	}
	if (keycode == KEY_D)
	{
		m->keys[keycode] = true;
		// player->pos_x += player->dir_y * speed;
		// player->pos_y -= player->dir_x * speed;
	}
	if (keycode == KEY_LEFT)
	{
		// float	old_dir_x = player->dir_x;
		// player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		// player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
		// float	old_plane_x = player->plane_x;
		// player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		// player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
		m->keys[0] = true;
	}
	if (keycode == KEY_RIGHT)
	{
		// float	old_dir_x = player->dir_x;
		// player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		// player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		// float	old_plane_x = player->plane_x;
		// player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		// player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
		m->keys[1] = true;
	}
	return (0);
}

int key_release_hook(int keycode, t_vars *m)
{
	// t_player *player = m->player;
	// float	speed = 0.1;
	// float	rot_speed = 0.1;
	// float	speed = m->fps->frame_time * 5.0;
	// float	rot_speed = m->fps->frame_time * 3.0;

	if (keycode == KEY_ESC)
		quit(keycode, m);
	if (keycode == KEY_W)
	{
		m->keys[keycode] = false;
		// player->pos_x += player->dir_x * speed;
		// player->pos_y += player->dir_y * speed;
	}
	if (keycode == KEY_S)
	{
		m->keys[keycode] = false;
		// player->pos_x -= player->dir_x * speed;
		// player->pos_y -= player->dir_y * speed;
	}
	if (keycode == KEY_A)
	{
		m->keys[keycode] = false;
		// player->pos_x -= player->dir_y * speed;
		// player->pos_y += player->dir_x * speed;
	}
	if (keycode == KEY_D)
	{
		m->keys[keycode] = false;
		// player->pos_x += player->dir_y * speed;
		// player->pos_y -= player->dir_x * speed;
	}
	if (keycode == KEY_LEFT)
	{
		m->keys[0] = false;
		// float	old_dir_x = player->dir_x;
		// player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		// player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
		// float	old_plane_x = player->plane_x;
		// player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		// player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
	}
	if (keycode == KEY_RIGHT)
	{
		m->keys[1] = false;
		// float	old_dir_x = player->dir_x;
		// player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		// player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		// float	old_plane_x = player->plane_x;
		// player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		// player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
	}
	return (0);
}

int	mouse_hook(int x, int y, t_vars *vars)
{
	(void)y;
	int		delta_x;

	float	delta_theta;
	t_player *player;

	player = vars->player;

	delta_x = x - vars->prev_mouse_x;
	delta_theta = delta_x * MOUSE_SPEED;

	float	old_dir_x;
	float	old_dir_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;

	player->dir_x = old_dir_x * cos(delta_theta) - old_dir_y * sin(delta_theta);
	player->dir_y = old_dir_x * sin(delta_theta) + old_dir_y * cos(delta_theta);

	float	old_plane_x;
	float	old_plane_y;

	old_plane_x = player->plane_x;
	old_plane_y = player->plane_y;

	player->plane_x = old_plane_x * cos(delta_theta) - old_plane_y * sin(delta_theta);
	player->plane_y = old_plane_x * sin(delta_theta) + old_plane_y * cos(delta_theta);

	// mlx_mouse_move(vars->mlx, vars->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	vars->prev_mouse_x = x;
	vars->prev_mouse_y = y;

	return (0);
}
