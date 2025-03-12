/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:31:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 07:18:07 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		rotate_player(float angle, t_player *player);
void		handle_interact(t_player *player, t_map *map_data);
static void	move_player(float move_x, float move_y, \
				t_player *player, t_map *map_data);
static void	get_moves(float *move_x, float *move_y, \
				t_player *player, t_fps *fps);
static bool	is_passable(int x, int y, t_map *map_data);

void	handle_player_controls(t_player *player, t_fps *fps, \
			t_map *map_data, t_vars *vars)
{
	float	move_x;
	float	move_y;
	float	rot_speed;

	move_x = 0.0;
	move_y = 0.0;
	player->is_moving = false;
	rot_speed = fps->frame_time * 2.5;
	if (player->interact == true)
		handle_interact(player, map_data);
	get_moves(&move_x, &move_y, player, fps);
	move_player(move_x, move_y, player, map_data);
	if (player->pan_left == true)
		rotate_player(-rot_speed, player);
	if (player->pan_right == true)
		rotate_player(rot_speed, player);
	if (player->torch_toggle == true)
		vars->max_brightness = 1.0f;
	else if (player->torch_toggle == false)
		vars->max_brightness = 0.4f;
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

static void	get_moves(float *move_x, float *move_y, \
				t_player *player, t_fps *fps)
{
	float	speed;

	speed = fps->frame_time * 2.5;
	if (player->move_left == true)
	{
		*move_x -= player->plane_x * speed;
		*move_y -= player->plane_y * speed;
	}
	if (player->move_right == true)
	{
		*move_x += player->plane_x * speed;
		*move_y += player->plane_y * speed;
	}
	if (player->move_forward == true)
	{
		*move_x += player->dir_x * speed;
		*move_y += player->dir_y * speed;
	}
	if (player->move_backward == true)
	{
		*move_x -= player->dir_x * speed;
		*move_y -= player->dir_y * speed;
	}
	if (fabsf(*move_x + *move_y) > 0)
		player->is_moving = true;
}

static void	move_player(float move_x, float move_y, \
				t_player *player, t_map *map_data)
{
	float	new_x;
	float	new_y;

	new_x = player->pos_x + move_x;
	new_y = player->pos_y + move_y;
	if (is_passable(new_x, player->pos_y, map_data) == true)
		player->pos_x += move_x;
	if (is_passable(player->pos_x, new_y, map_data) == true)
		player->pos_y += move_y;
}

static bool	is_passable(int x, int y, t_map *map_data)
{
	int		i;
	char	**map;
	t_door	*doors;

	i = 0;
	doors = map_data->doors;
	map = map_data->map;
	if (map[y][x] != '0')
		return (false);
	while (i < map_data->door_count)
	{
		if (doors[i].x == x && doors[i].y == y && doors[i].is_open == false)
			return (false);
		i++;
	}
	return (true);
}
