/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:40 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 08:14:11 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "graphics.h"

int				apply_opacity(int color, int opacity);
void			init_ray(int x, t_player *player, t_ray *ray);
void			find_step_and_dist(t_ray *ray, t_player *player);
static void		do_dda(t_ray *ray, t_map *map_data, char **map);
static void		get_wall_height(t_ray *ray);
void			render_open_door(t_vars *vars, int x);
void			floor_casting(t_vars *vars, t_player *player, t_map *map_data);
int				check_door_hit(t_ray *ray, t_map *map_data);
void			get_closed_door_height(t_ray *ray);
t_tex_data		get_tex_data(int x, t_ray *ray, t_player *player, t_vars *vars);
void			draw_textured_column(int x, t_ray *ray, \
					t_tex_data *tex_data, t_vars *vars);
void			update_doors(t_map *map_data);

void	raycast(t_vars *vars)
{
	t_player	*player;
	t_ray		ray;
	t_tex_data	tex_data;
	int			x;

	player = vars->player;
	x = -1;
	update_doors(vars->map_data);
	floor_casting(vars, player, vars->map_data);
	while (++x < WIN_WIDTH)
	{
		init_ray(x, player, &ray);
		find_step_and_dist(&ray, player);
		do_dda(&ray, vars->map_data, vars->map_data->map);
		get_wall_height(&ray);
		tex_data = get_tex_data(x, &ray, player, vars);
		draw_textured_column(x, &ray, &tex_data, vars);
		if (ray.door)
			render_open_door(vars, x);
	}
}

void	init_ray(int x, t_player *player, t_ray *ray)
{
	ray->door = NULL;
	ray->first_door = NULL;
	ray->camera_x = 2 * x / (float)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e7;
	else
		ray->delta_dist_x = fabsf(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e7;
	else
		ray->delta_dist_y = fabsf(1 / ray->dir_y);
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
