/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:31:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/12 13:21:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(float angle, t_player *player);
void	move_player(float move_x, float move_y, t_player *player, t_map *map_data);
void	get_moves(float *move_x, float *move_y, t_player *player, t_fps *fps);
bool	is_passable(int x, int y, t_map *map_data);
void	handle_interact(t_player *player, t_map *map_data);

void	handle_player_controls(t_player *player, t_fps *fps, t_map *map_data)
{
	float	move_x;
	float	move_y;
	float	rot_speed;
	t_door	*doors;

	move_x = 0.0;
	move_y = 0.0;
	rot_speed = fps->frame_time * 2.5;
	doors = map_data->doors;
	if (player->interact == true)
		handle_interact(player, map_data);
	get_moves(&move_x, &move_y, player, fps);
	move_player(move_x, move_y, player, map_data);
	if (player->pan_left == true)
		rotate_player(-rot_speed, player);
	if (player->pan_right == true)
		rotate_player(rot_speed, player);
}

void	update_door_status(t_map *map_data)
{
	int		i;
	t_door	*doors;

	i = 0;
	doors = map_data->doors;
	while (i < map_data->door_count)
	{
		if (doors[i].is_open == true)
			map_data->map[doors[i].y][doors[i].x] = '0';
		else if (doors[i].is_open == false)
			map_data->map[doors[i].y][doors[i].x] = 'D';
		i++;
	}
}

void	handle_interact(t_player *player, t_map *map_data)
{
	int		interact_range;
	int		i;
	t_door	*doors;

	interact_range = 1.0;
	i = 0;
	doors = map_data->doors;
	while (i < map_data->door_count)
	{
		if ((int)(player->pos_x + (player->dir_x * interact_range)) == doors[i].x && \
			(int)(player->pos_y + (player->dir_y * interact_range)) == doors[i].y)
		{
				doors[i].is_open = !doors[i].is_open;
		}
		i++;
	}
	update_door_status(map_data);
	player->interact = false;
}

void	get_moves(float *move_x, float *move_y, t_player *player, t_fps *fps)
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
}

void	move_player(float move_x, float move_y, t_player *player, t_map *map_data)
{
	float	new_x;
	float	new_y;
	t_door	*doors;

	new_x = player->pos_x + move_x;
	new_y = player->pos_y + move_y;
	doors = map_data->doors;
	if (is_passable(new_x, player->pos_y, map_data) == true)
		player->pos_x += move_x;
	if (is_passable(player->pos_x, new_y, map_data) == true)
		player->pos_y += move_y;
}

bool	is_passable(int x, int y, t_map *map_data)
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
