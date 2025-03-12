/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:41:37 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 09:24:07 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		draw_floor_pixel(int opacity, t_vars *vars, \
					t_point tex_coord, t_point window);
static void		draw_ceiling_pixel(int opacity, t_vars *vars, \
					t_point tex_coord, t_point window);
static t_point	get_tex_coords(t_fpoint floor_pos, \
					int tex_width, int tex_height);

void	draw_floor_and_ceiling_row(float row_distance, t_floor *floor, \
			t_vars *vars, t_point window)
{
	t_point		tex_coord;
	t_map		*map_data;
	int			opacity;

	map_data = vars->map_data;
	opacity = fmaxf(0.0f, 1.0f - (row_distance / (VISIBLE_RANGE))) \
				* 255 * vars->max_brightness;
	window.x = 0;
	while (window.x < WIN_WIDTH)
	{
		tex_coord = get_tex_coords(floor->pos, map_data->tex_width, \
							map_data->tex_height);
		floor->pos.x += floor->step.x;
		floor->pos.y += floor->step.y;
		draw_floor_pixel(opacity, vars, tex_coord, window);
		draw_ceiling_pixel(opacity, vars, tex_coord, window);
		window.x++;
	}
}

static void	draw_floor_pixel(int opacity, t_vars *vars, \
				t_point tex_coord, t_point window)
{
	int		color;
	int		texture_index;
	t_map	*map_data;

	map_data = vars->map_data;
	texture_index = map_data->tex_width * tex_coord.y + tex_coord.x;
	if (map_data->texture_count < 6)
		color = map_data->floor_color;
	else
		color = map_data->texture[FLOOR][texture_index];
	color = apply_opacity(color, opacity);
	put_pixel(window.x, window.y, color, &vars->img);
}

static void	draw_ceiling_pixel(int opacity, t_vars *vars, \
				t_point tex_coord, t_point window)
{
	int		color;
	int		texture_index;
	t_map	map_data;

	map_data = *vars->map_data;
	texture_index = map_data.tex_width * tex_coord.y + tex_coord.x;
	if (map_data.texture_count < 6)
		color = map_data.ceiling_color;
	else
		color = map_data.texture[CEILING][texture_index];
	color = (color >> 1) & 8355711;
	color = apply_opacity(color, opacity);
	put_pixel(window.x, WIN_HEIGHT - window.y - 1, color, &vars->img);
}

static t_point	get_tex_coords(t_fpoint floor_pos, \
					int tex_width, int tex_height)
{
	t_point	tex_coord;
	t_point	cell;

	cell.x = (int)floor_pos.x;
	cell.y = (int)floor_pos.y;
	tex_coord.x = (int)(tex_width * (floor_pos.x - cell.x)) & (tex_width - 1);
	tex_coord.y = (int)(tex_height * (floor_pos.y - cell.y)) & (tex_height - 1);
	return (tex_coord);
}
