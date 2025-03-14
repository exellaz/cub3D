/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:40:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/14 08:39:06 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void			draw_floor_and_ceiling_row(float row_distance, t_floor *floor, \
					t_vars *vars, t_point window);
static void		get_floor_step(float row_distance, t_floor *floor, \
					t_fpoint left_ray_dir, t_fpoint right_ray_dir);
static void		get_floor_pos(float row_distance, t_floor *floor, \
					t_fpoint left_ray_dir, t_player *player);
static float	get_row_distance(int y);

void	render_floor_and_ceiling(t_vars *vars, t_player *player)
{
	t_point		window;
	t_fpoint	left_ray_dir;
	t_fpoint	right_ray_dir;
	t_floor		floor;
	float		row_distance;

	left_ray_dir.x = player->dir_x - player->plane_x;
	left_ray_dir.y = player->dir_y - player->plane_y;
	right_ray_dir.x = player->dir_x + player->plane_x;
	right_ray_dir.y = player->dir_y + player->plane_y;
	window.y = WIN_HEIGHT / 2;
	while (window.y < WIN_HEIGHT)
	{
		row_distance = get_row_distance(window.y);
		get_floor_pos(row_distance, &floor, left_ray_dir, player);
		get_floor_step(row_distance, &floor, left_ray_dir, right_ray_dir);
		draw_floor_and_ceiling_row(row_distance, &floor, vars, window);
		window.y++;
	}
}

static void	get_floor_step(float row_distance, t_floor *floor, \
				t_fpoint left_ray_dir, t_fpoint right_ray_dir)
{
	floor->step.x = row_distance * (right_ray_dir.x - \
						left_ray_dir.x) / WIN_WIDTH;
	floor->step.y = row_distance * (right_ray_dir.y - \
						left_ray_dir.y) / WIN_WIDTH;
}

static void	get_floor_pos(float row_distance, t_floor *floor, \
				t_fpoint left_ray_dir, t_player *player)
{
	floor->pos.x = player->pos_x + row_distance * left_ray_dir.x;
	floor->pos.y = player->pos_y + row_distance * left_ray_dir.y;
}

static float	get_row_distance(int y)
{
	return ((0.5f * WIN_HEIGHT) / (y - WIN_HEIGHT * 0.5));
}
