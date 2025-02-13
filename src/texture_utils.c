/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:29 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/13 12:41:35 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "graphics.h"

void			draw_textured_column(int x, t_ray *ray, \
					t_tex_data *tex_data, t_vars *vars);
static float	get_wall_x(t_ray *ray, t_player *player);
static int		get_tex_x(float wall_x, t_ray *ray);
static int		get_tex_num(t_ray *ray);
static void		get_tex_step_and_pos(t_ray *ray, t_tex_data *tex_data);

void	get_textures(int x, t_ray *ray, t_player *player, t_vars *vars)
{
	t_tex_data	tex_data;

	tex_data.wall_x = get_wall_x(ray, player);
	tex_data.tex_x = get_tex_x(tex_data.wall_x, ray);
	tex_data.tex_num = get_tex_num(ray);
	if (vars->map_data->map[ray->map_y][ray->map_x] == 'D')
		tex_data.tex_num = vars->map_data->texture_count - 1;
	get_tex_step_and_pos(ray, &tex_data);
	draw_textured_column(x, ray, &tex_data, vars);
}

static float	get_wall_x(t_ray *ray, t_player *player)
{
	float	wall_x;

	if (ray->wall_side == 1)
		wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	else
		wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_tex_x(float wall_x, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(wall_x * (float)TEX_WIDTH);
	if (ray->wall_side == 0 && ray->dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->wall_side == 1 && ray->dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

static int	get_tex_num(t_ray *ray)
{
	int	tex_num;

	if (ray->wall_side == 1)
	{
		if (ray->dir_y < 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	else
	{
		if (ray->dir_x < 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	return (tex_num);
}

static void	get_tex_step_and_pos(t_ray *ray, t_tex_data *tex_data)
{
	tex_data->step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_data->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 \
						+ ray->line_height / 2) * tex_data->step;
}
