/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:11:05 by we                #+#    #+#             */
/*   Updated: 2025/03/04 15:41:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3D.h"
#include <mlx.h>

#include "events.h"

void	rotate_player(float angle, t_player *player);
void	handle_toggles(int keycode, t_player *player, t_vars *vars);
void	handle_movement(int keycode, t_player *player, bool state);
int		quit(int keycode, t_vars *m);

int	key_press_hook(int keycode, t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	if (keycode == XK_Escape)
		quit(keycode, vars);
	if (keycode == XK_Left)
		player->pan_left = true;
	if (keycode == XK_Right)
		player->pan_right = true;
	if (keycode == XK_e)
		player->interact = true;
	handle_movement(keycode, player, true);
	handle_toggles(keycode, player, vars);
	return (0);
}

int	key_release_hook(int keycode, t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	handle_movement(keycode, player, false);
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
