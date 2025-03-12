/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:39:46 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 09:47:54 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <X11/keysym.h>

int	quit(int keycode, t_vars *vars)
{
	(void)keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img.img);
	free_texture(vars->map_data->texture_data, vars->mlx);
	mem_clean();
	free(vars->mlx);
	exit(0);
	return (0);
}

void	handle_toggles(int keycode, t_player *player, t_vars *vars)
{
	if (keycode == XK_m && vars->minimap_toggle == false)
		vars->minimap_toggle = true;
	else if (keycode == XK_m)
		vars->minimap_toggle = false;
	if (keycode == XK_t && player->torch_toggle == false)
		player->torch_toggle = true;
	else if (keycode == XK_t)
		player->torch_toggle = false;
}

void	handle_movement(int keycode, t_player *player, bool state)
{
	if (keycode == XK_w)
		player->move_forward = state;
	if (keycode == XK_s)
		player->move_backward = state;
	if (keycode == XK_a)
		player->move_left = state;
	if (keycode == XK_d)
		player->move_right = state;
}

void	handle_interact(t_player *player, t_map *map_data)
{
	int		i;
	int		range;
	t_door	*doors;

	range = 1.0;
	doors = map_data->doors;
	i = 0;
	while (i < map_data->door_count)
	{
		if ((int)(player->pos_x + (player->dir_x * range)) == doors[i].x && \
			(int)(player->pos_y + (player->dir_y * range)) == doors[i].y)
		{
			doors[i].is_open = !doors[i].is_open;
		}
		i++;
	}
	player->interact = false;
}
