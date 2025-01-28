/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/01/28 15:12:51 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"
#include "math.h"
#include "stdio.h"
#include <X11/keysym.h>

void	rotate_player(float angle, t_player *player);

int	quit(int keycode, t_vars *m)
{
	(void)keycode;
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

int key_press_hook(int keycode, t_vars *m)
{
	if (keycode == XK_Escape)
		quit(keycode, m);
	if (keycode == XK_w)
		m->keys[KEY_W] = true;
	if (keycode == XK_s)
		m->keys[KEY_S] = true;
	if (keycode == XK_a)
		m->keys[KEY_A] = true;
	if (keycode == XK_d)
		m->keys[KEY_D] = true;
	if (keycode == XK_Left)
		m->keys[KEY_LEFT] = true;
	if (keycode == XK_Right)
		m->keys[KEY_RIGHT] = true;
	return (0);
}

int key_release_hook(int keycode, t_vars *m)
{
	if (keycode == XK_Escape)
		quit(keycode, m);
	if (keycode == XK_w)
		m->keys[KEY_W] = false;
	if (keycode == XK_s)
		m->keys[KEY_S] = false;
	if (keycode == XK_a)
		m->keys[KEY_A] = false;
	if (keycode == XK_d)
		m->keys[KEY_D] = false;
	if (keycode == XK_Left)
		m->keys[KEY_LEFT] = false;
	if (keycode == XK_Right)
		m->keys[KEY_RIGHT] = false;
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
	if (delta_x == 0)
		return (0);
	delta_theta = delta_x * MOUSE_SPEED;
	rotate_player(delta_theta, player);
	mlx_mouse_move(vars->mlx, vars->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	vars->prev_mouse_x = WIN_WIDTH / 2;
	return (0);
}

void	rotate_player(float angle, t_player *player)
{
	float	old_dir_x;
	float	old_dir_y;
	float	old_plane_x;
	float	old_plane_y;

	old_dir_x = player->dir_x;
	old_dir_y = player->dir_y;
	old_plane_x = player->plane_x;
	old_plane_y = player->plane_y;
	player->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	player->plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);
}