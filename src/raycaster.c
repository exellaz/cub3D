/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/05 16:59:10 by kkhai-ki         ###   ########.fr       */
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

static void	init_ray(int x, t_player *player, t_ray *ray)
{
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

static void	find_step_and_dist(t_ray *ray, t_player *player)
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

static void	do_dda(t_ray *ray, t_map *map_data, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->wall_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->wall_side = 1;
		}
		if (ray->map_x > map_data->width || ray->map_y > map_data->width || ray->map_x < 0 || ray->map_y < 0 || map[ray->map_y][ray->map_x] != '0')
			hit = 1;
	}
}

static void	render_walls(t_ray *ray)
{
	if (ray->wall_side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

int apply_opacity(int color, float opacity);

static void		get_textures(int x, t_ray *ray, t_player *player, t_vars *mlx)
{
	int				texNum = mlx->map[ray->map_y][ray->map_x] - 49;
	int				**texture = mlx->texture;
	float			wallX;
	int				texX;
	float			step;
	float			texPos;
	int				texY;
	unsigned int	color;

	// printf("texNum: %d\n", texNum);
	if (ray->wall_side == 0)
		wallX = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wallX = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wallX -= floor((wallX));

	texX = (int)(wallX * (float)TEX_WIDTH);

	if (ray->wall_side == 0 && ray->dir_x > 0)
		texX = TEX_WIDTH - texX - 1;
	if (ray->wall_side == 1 && ray->dir_y < 0)
		texX = TEX_WIDTH - texX - 1;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	texPos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;

	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		// printf("%c\n", mlx->map[ray->map_y][ray->map_x]);
		// printf("%d\n", texNum);
		color = texture[texNum][TEX_HEIGHT * texY + texX];
		// color = 0xFFFFFF;

		if (ray->wall_side == 1)
			color = (color >> 1) & 8355711;
		// float	distance;
		// float	opacity;

		// distance = sqrt(pow(ray->map_x - player->pos_x, 2) + pow(ray->map_y - player->pos_y, 2));
		// opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
		// color = apply_opacity(color, opacity);
		put_pixel(x, y, color, &mlx->img);
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
		do_dda(ray, mlx->map_data, mlx->map);
		render_walls(ray);
		get_textures(x, ray, player, mlx);
		x++;
	}
}
