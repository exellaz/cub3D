/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/02/02 13:57:02 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>

#include "graphics.h"
#include "enum.h"
#include "events.h"
#include "math.h"
#include "stdio.h"
#include "cub3D.h"
#include <X11/keysym.h>

void	rotate_player(float angle, t_player *player);

int	quit(int keycode, t_vars *m)
{
	(void)keycode;
	mlx_destroy_window(m->mlx, m->win);
	exit(0);
	return (0);
}

int	key_press_hook(int keycode, t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	if (keycode == XK_Escape)
		quit(keycode, vars);
	if (keycode == XK_m && vars->minimap_toggle == false)
		vars->minimap_toggle = true;
	else if (keycode == XK_m)
		vars->minimap_toggle = false;
	if (keycode == XK_w)
		player->move_forward = true;
	if (keycode == XK_s)
		player->move_backward = true;
	if (keycode == XK_a)
		player->move_left = true;
	if (keycode == XK_d)
		player->move_right = true;
	if (keycode == XK_Left)
		player->pan_left = true;
	if (keycode == XK_Right)
		player->pan_right = true;
	if (keycode == XK_e)
		player->interact = true;
	return (0);
}

int	key_release_hook(int keycode, t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	if (keycode == XK_w)
		player->move_forward = false;
	if (keycode == XK_s)
		player->move_backward = false;
	if (keycode == XK_a)
		player->move_left = false;
	if (keycode == XK_d)
		player->move_right = false;
	if (keycode == XK_Left)
		player->pan_left = false;
	if (keycode == XK_Right)
		player->pan_right = false;
	if (keycode == XK_e)
		player->interact = false;
	return (0);
}

int	mouse_hook(int x, int y, t_vars *vars)
{
	int			delta_x;
	float		delta_theta;
	t_player	*player;

	(void)y;
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
