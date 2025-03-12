/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:03:35 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 10:04:42 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	do_dda(t_ray *ray, t_map *map_data, char **map);
static void	get_wall_height(t_ray *ray);
static int	check_door_hit(t_ray *ray, t_map *map_data);
static void	get_closed_door_height(t_ray *ray);

void	render_walls(t_vars *vars, t_player *player, t_map *map_data)
{
	int			x;
	t_ray		ray;
	t_tex_data	tex_data;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(x, player, &ray);
		find_step_and_dist(&ray, player);
		do_dda(&ray, map_data, map_data->map);
		get_wall_height(&ray);
		tex_data = get_tex_data(x, &ray, player, vars);
		draw_textured_column(x, &ray, &tex_data, vars);
		if (ray.door)
			render_open_door(vars, x);
		x++;
	}
}

static void	do_dda(t_ray *ray, t_map *map_data, char **map)
{
	int		hit;

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
		if ((ray->map_x > map_data->width || ray->map_y > map_data->height || \
			ray->map_x < 0 || ray->map_y < 0 || \
			(map[ray->map_y][ray->map_x] == '1')))
			hit = 1;
		if (map[ray->map_y][ray->map_x] == 'D')
			hit = check_door_hit(ray, map_data);
	}
}

static void	get_wall_height(t_ray *ray)
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
	if (ray->door)
		get_closed_door_height(ray);
}

static int	check_door_hit(t_ray *ray, t_map *map_data)
{
	ray->door = find_door(map_data, ray->map_x, ray->map_y);
	if (!ray->first_door)
		ray->first_door = ray->door;
	if (ray->door != ray->first_door && ray->door->is_open == false)
		return (1);
	return (0);
}

static void	get_closed_door_height(t_ray *ray)
{
	float	door_depth;
	int		door_height;
	int		door_start;
	int		door_end;

	door_depth = ray->perp_wall_dist + (ray->door->progress * 0.5);
	door_height = (int)(WIN_HEIGHT / door_depth);
	door_start = -(door_height) / 2 + WIN_HEIGHT / 2;
	door_end = door_height / 2 + WIN_HEIGHT / 2;
	if (door_start < 0)
		door_start = 0;
	if (door_end >= WIN_HEIGHT)
		door_end = WIN_HEIGHT - 1;
	if (door_depth < ray->perp_wall_dist)
	{
		ray->draw_start = door_start;
		ray->draw_end = door_end;
	}
}
