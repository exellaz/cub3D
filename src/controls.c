/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:31:18 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/04 15:15:51 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(float angle, t_player *player);
void	move_player(float move_x, float move_y, char **map, t_player *player, t_door *doors);
void	get_moves(float *move_x, float *move_y, t_player *player, t_fps *fps);
bool	is_passable(int x, int y, char **map, t_door *doors);
void	handle_interact(t_player *player, t_door *doors);

void	handle_player_controls(char **map, t_player *player, t_fps *fps, t_door *doors)
{
	float	move_x;
	float	move_y;
	float	rot_speed;

	move_x = 0.0;
	move_y = 0.0;
	rot_speed = fps->frame_time * 2.5;
	if (player->interact == true)
		handle_interact(player, doors);
	get_moves(&move_x, &move_y, player, fps);
	move_player(move_x, move_y, map, player, doors);
	if (player->pan_left == true)
		rotate_player(-rot_speed, player);
	if (player->pan_right == true)
		rotate_player(rot_speed, player);
}

void	handle_interact(t_player *player, t_door *doors)
{
	int	interact_range;

	interact_range = 1.0;
	if ((int)(player->pos_x + (player->dir_x * interact_range)) == doors[0].x && \
			(int)(player->pos_y + (player->dir_y * interact_range)) == doors[0].y)
	{
		doors[0].is_open = !doors[0].is_open;
	}
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

void	move_player(float move_x, float move_y, char **map, t_player *player, t_door *doors)
{
	float	new_x;
	float	new_y;

	new_x = player->pos_x + move_x;
	new_y = player->pos_y + move_y;
	(void)doors;
	if (is_passable(new_x, player->pos_y, map, doors) == true)
		player->pos_x += move_x;
	if (is_passable(player->pos_x, new_y, map, doors) == true)
		player->pos_y += move_y;
}

bool	is_passable(int x, int y, char **map, t_door *doors)
{
	if (map[y][x] != '0' && map[y][x] != '2')
		return (false);
	if (doors[0].x == x && doors[0].y == y && doors[0].is_open == false)
		return (false);
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
