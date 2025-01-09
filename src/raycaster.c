/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/01/09 13:23:13 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	ray_collision(float px, float py, t_mlx *mlx)
{
	int	x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;

	if (x < 0 || y < 0 || x >= WIN_WIDTH / BLOCK_SIZE || y >= WIN_HEIGHT / BLOCK_SIZE + 1)
		return (true);
	if (y < 10 && x < 14 && mlx->map[y][x] == '1') // Change 10 and 14 to width and height of map
		return (true);
	return (false);
}

static float	distance(float x, float y) // Calculates the distance with a fish-eye distortion
{
	return sqrt(x * x + y * y);
}

static float fixed_dist(float x1, float y1, float x2, float y2, t_player *player)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - player->angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	draw_ray(t_player *player, t_mlx *mlx, float start_x, int i)
{
	(void)i;
	float	ray_x = player->x + 16;
	float	ray_y = player->y + 16;
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);

	while (!ray_collision(ray_x, ray_y, mlx))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, &mlx->img); // Draw rays in 2D
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	// float	dist = distance(ray_x - player->x, ray_y - player->y); // has fish-eye distortion
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, player);
	float	height = (BLOCK_SIZE / dist) * (WIN_WIDTH / 2);
	int		start_y = (WIN_HEIGHT - height) / 2;
	int		end = start_y + height;
	while (start_y < end)
	{
		// put_pixel(i, start_y, 255, &mlx->img); // Render in 3D
		start_y++;
	}
	return (0);
}