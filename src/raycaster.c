/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/28 20:54:43 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "graphics.h"

int				apply_opacity(int color, float opacity);
void			init_ray(int x, t_player *player, t_ray *ray);
void			find_step_and_dist(t_ray *ray, t_player *player);
void			do_dda(t_ray *ray, t_map *map_data, char **map);
void			get_wall_height(t_ray *ray);
void			door_casting(t_vars *vars, int x);

void	floor_casting(t_vars *vars)
{
	t_player	*player = vars->player;
	t_map		*map_data = vars->map_data;
	int			tex_width = map_data->tex_width;
	int			tex_height = map_data->tex_height;

	float	ray_dir_x0 = player->dir_x - player->plane_x;
	float	ray_dir_y0 = player->dir_y - player->plane_y;
	float	ray_dir_x1 = player->dir_x + player->plane_x;
	float	ray_dir_y1 = player->dir_y + player->plane_y;

	float	pos_z = 0.5 * WIN_HEIGHT;

	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
	{
		int	p = y - WIN_HEIGHT / 2;
		float	row_distance = pos_z / p;
		float	floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIN_WIDTH;
		float	floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIN_WIDTH;

		float	floor_x = player->pos_x + row_distance * ray_dir_x0;
		float	floor_y = player->pos_y + row_distance * ray_dir_y0;
		float	opacity = fmax(0.0, 1.0 - (row_distance / (VISIBLE_RANGE)));
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			int	cell_x = (int)floor_x;
			int	cell_y = (int)floor_y;

			int	tx = (int)(tex_width * (floor_x - cell_x)) & (tex_width - 1);
			int	ty = (int)(tex_height * (floor_y - cell_y)) & (tex_height - 1);

			floor_x += floor_step_x;
			floor_y += floor_step_y;

			int	color;

			if (map_data->texture_count < 6)
				color = map_data->floor_color;
			else
				color = map_data->texture[FLOOR][tex_width * ty + tx];
			color = apply_opacity(color, opacity);
			put_pixel(x, y, color, &vars->img);
			if (map_data->texture_count < 6)
				color = map_data->ceiling_color;
			else
				color = map_data->texture[CEILING][tex_width * ty + tx];
			color = (color >> 1) & 8355711;
			color = apply_opacity(color, opacity);
			put_pixel(x, WIN_HEIGHT - y - 1, color, &vars->img);
		}
	}
}

void update_doors(t_map *map_data)
{
	for (int i = 0; i < map_data->door_count; i++)
	{
		t_door *door = &map_data->doors[i];
		if (door->is_open && door->progress < 1.0)
		{
			door->progress += 0.05;
			if (door->progress > 1.0)
				door->progress = 1.0;
		}
		else if (!door->is_open && door->progress > 0.0)
		{
			door->progress -= 0.05;
			if (door->progress < 0.0)
				door->progress = 0.0;
		}
		if (door->is_open == true && door->progress == 1.0)
			map_data->map[door->y][door->x] = '0';
		else if (door->is_open == false)
			map_data->map[door->y][door->x] = 'D';
	}
}

void	raycast(t_vars *vars)
{
	t_player	*player;
	t_ray		ray;
	int			x;

	player = vars->player;
	x = -1;
	update_doors(vars->map_data);
	floor_casting(vars);
	while (++x < WIN_WIDTH)
	{
		init_ray(x, player, &ray);
		find_step_and_dist(&ray, player);
		do_dda(&ray, vars->map_data, vars->map_data->map);
		get_wall_height(&ray);
		get_textures(x, &ray, player, vars);
		if (ray.door)
			door_casting(vars, x);
	}
}

void	init_ray(int x, t_player *player, t_ray *ray)
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

t_door	*find_door(t_map *map_data, int x, int y)
{
	int		i;
	t_door	*doors;
	t_door	*door;

	i = 0;
	doors = map_data->doors;
	while (i < map_data->door_count)
	{
		if (doors[i].x == x && doors[i].y == y)
		{
			door = &doors[i];
			return (door);
		}
		i++;
	}
	return (NULL);
}

void	do_dda(t_ray *ray, t_map *map_data, char **map)
{
	int	hit;
	t_door	*first_door;

	hit = 0;
	ray->door = NULL;
	first_door = NULL;
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
			(map[ray->map_y][ray->map_x] != 'D' && map[ray->map_y][ray->map_x] != '0')))
			hit = 1;
		if (map[ray->map_y][ray->map_x] == 'D')
		{
			ray->door = find_door(map_data, ray->map_x, ray->map_y);
			if (!first_door)
				first_door = ray->door;
			if (ray->door->is_open == false && ray->door != first_door)
				hit = 1;
		}
	}
}

void	get_wall_height(t_ray *ray)
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
	{
		float door_depth = ray->perp_wall_dist + (ray->door->progress * 0.5);
		int door_height = (int)(WIN_HEIGHT / door_depth);
		int door_start = -(door_height) / 2 + WIN_HEIGHT / 2;
		int door_end = door_height / 2 + WIN_HEIGHT / 2;

		if (door_start < 0)
			door_start = 0;
		if (door_end >= WIN_HEIGHT)
			door_end = WIN_HEIGHT - 1;

		// Ensure the door does NOT override closer walls
		if (door_depth < ray->perp_wall_dist)
		{
			ray->draw_start = door_start;
			ray->draw_end = door_end;
		}
	}
}
