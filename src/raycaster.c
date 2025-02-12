/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/12 16:01:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "graphics.h"

unsigned int	apply_opacity(unsigned int color, float opacity);
static void		init_ray(int x, t_player *player, t_ray *ray);
static void		find_step_and_dist(t_ray *ray, t_player *player);
static void		do_dda(t_ray *ray, t_map *map_data, char **map);
static void		render_walls(t_ray *ray);

void	draw_floor_and_ceiling(t_vars *vars, t_player *player)
{
	int	y, x;
	float	row_dist;
	float	floor_x, floor_y;
	float	ray_dir_x0, ray_dir_y0;
	float	ray_dir_x1, ray_dir_y1;

	ray_dir_x0 = player->dir_x + player->plane_x;
	ray_dir_y0 = player->dir_y + player->plane_y;
	ray_dir_x1 = player->dir_x + player->plane_x;
	ray_dir_y1 = player->dir_y + player->plane_y;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		row_dist = (0.5 * WIN_HEIGHT) / (y - WIN_HEIGHT / 2);

		floor_x = player->pos_x + row_dist * (ray_dir_x1 - ray_dir_x0);
		floor_y = player->pos_y + row_dist * (ray_dir_y1 - ray_dir_y0);

		x = 0;
		while (x < WIN_WIDTH)
		{
			int tex_x = (int)(floor_x * TEX_WIDTH) % TEX_WIDTH;
			int tex_y = (int)(floor_y * TEX_HEIGHT) % TEX_HEIGHT;

			unsigned int color = 0x696969;

			float opacity = fmax(0.0, 1.0 - (row_dist / (VISIBLE_RANGE * 2)));
			color = apply_opacity(color, opacity);

			put_pixel(x, y, color, &vars->img);

			unsigned int ceiling_color = 0x384147;
			ceiling_color = apply_opacity(ceiling_color, opacity);
			put_pixel(x, WIN_HEIGHT - y, ceiling_color, &vars->img);

			x++;
		}
		y++;
	}
}

void	raycast(t_vars *vars)
{
	t_player	*player;
	t_ray		*ray;
	int			x;

	player = vars->player;
	ray = &player->ray;
	x = 0;
	draw_floor_and_ceiling(vars, player);
	while (x < WIN_WIDTH)
	{
		init_ray(x, player, ray);
		find_step_and_dist(ray, player);
		do_dda(ray, vars->map_data, vars->map_data->map);
		render_walls(ray);
		get_textures(x, ray, player, vars);
		x++;
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
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) \
							* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) \
							* ray->delta_dist_y;
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
		if (ray->map_x > map_data->width || ray->map_y > map_data->width || \
			ray->map_x < 0 || ray->map_y < 0 || \
			map[ray->map_y][ray->map_x] != '0')
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

