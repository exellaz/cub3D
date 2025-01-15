/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/01/15 14:32:55 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_line(t_point start, t_point end, int color, t_img *img)
{
	int dx = fabs(end.x - start.x);
	int dy = fabs(end.y - start.y);
	int sx = (start.x < end.x) ? 1 : -1;
	int sy = (start.y < end.y) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		put_pixel(start.x, start.y, color, img);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void	init_ray(int x, t_player *player, t_ray *ray)
{
	ray = &player->ray;
	ray->camera_x = 2 * x / (float)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e7;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e7;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	find_step_and_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void	raycast(t_vars *mlx)
{
	t_player	*player;
	t_ray		*ray;
	int			x;

	player = mlx->player;
	ray = &player->ray;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(x, player, ray);
		find_step_and_dist(ray, player);

		int	hit = 0;
		int	side;

		while (hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				side = 1;
			}
			if (ray->map_x > 13 || ray->map_y > 10 || ray->map_x < 0 || ray->map_y < 0 || mlx->map[ray->map_y][ray->map_x] == '1')
			{
				hit = 1;
				// draw_square(ray->map_x * BLOCK_SIZE, ray->map_y * BLOCK_SIZE, BLOCK_SIZE, 0xFF0000, &mlx->img);
			}
		}

		// t_point start = {round(player->pos_x * BLOCK_SIZE), round(player->pos_y * BLOCK_SIZE)};
		// t_point end = {ray->map_x * BLOCK_SIZE, ray->map_y * BLOCK_SIZE};
		// draw_line(start, end, 0xFF0000, &mlx->img);

		if (side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

		int line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);

		int	draw_start = -line_height / 2 + WIN_HEIGHT / 2;

		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

		while (draw_start < draw_end)
		{
			put_pixel(x, draw_start, 255, &mlx->img);
			draw_start++;
		}
		x++;
	}
}