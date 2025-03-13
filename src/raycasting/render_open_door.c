/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_open_door.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:51:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/13 13:17:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	do_door_dda(t_ray *ray, t_map *map_data, char **map);
static void	get_open_door_height(t_ray *ray);

void	render_open_door(t_vars *vars, int x)
{
	t_player	*player;
	t_ray		ray;
	t_tex_data	tex_data;

	player = vars->player;
	init_ray(x, player, &ray);
	find_step_and_dist(&ray, player);
	do_door_dda(&ray, vars->map_data, vars->map_data->map);
	get_open_door_height(&ray);
	tex_data = get_tex_data(&ray, player, vars);
	draw_textured_column(x, &ray, &tex_data, vars);
	x++;
}

static void	do_door_dda(t_ray *ray, t_map *map_data, char **map)
{
	int	hit;

	hit = 0;
	ray->door = NULL;
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
		if ((ray->map_x > map_data->width || ray->map_y > map_data->height || \
			ray->map_x < 0 || ray->map_y < 0 || \
			map[ray->map_y][ray->map_x] == 'D'))
			hit = 1;
		if (map[ray->map_y][ray->map_x] == 'D')
			ray->door = find_door(map_data, ray->map_x, ray->map_y);
	}
}

static void	get_open_door_height(t_ray *ray)
{
	int	offset;

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
	if (ray->door)
	{
		offset = (int)(ray->line_height * ray->door->progress);
		ray->draw_end -= offset;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		if (ray->draw_end < 0)
			ray->draw_end = 0;
	}
}
