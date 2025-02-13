/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:51:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/13 21:52:05 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "defines.h"

unsigned int	apply_opacity(unsigned int color, float opacity);
void		init_ray(int x, t_player *player, t_ray *ray);
void		find_step_and_dist(t_ray *ray, t_player *player);
void		do_dda(t_ray *ray, t_map *map_data, char **map);
void		render_walls(t_ray *ray);


void	add_door_offset(t_ray *ray)
{
	float	vertical_offset;
	float	progress;

	vertical_offset = 0;
	progress = ray->door->progress;
	vertical_offset = -(ray->line_height) * progress;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + WIN_HEIGHT / 2 + vertical_offset;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	door_raycast(t_vars *vars)
{
	int			x;
	t_player	*player;
	t_ray		ray;

	player = vars->player;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(x, player, &ray);
		find_step_and_dist(&ray, player);
		do_dda(&ray, vars->map_data, vars->map_data->map);
		add_door_offset(&ray);
		render_walls(&ray);
		get_textures(x, &ray, player, vars);
		x++;
	}
}