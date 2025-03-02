/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:07:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/02 19:18:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "defines.h"

static int	get_tex_color(int y, t_tex_data *tex_data, \
				t_vars *vars, t_ray *ray);

void	draw_textured_column(int x, t_ray *ray, \
			t_tex_data *tex_data, t_vars *vars)
{
	int	color;
	int	y;

	tex_data->base_opacity = fmaxf(0.0f, 1.0f \
			- (ray->perp_wall_dist / (VISIBLE_RANGE))) * 255 * vars->max_brightness;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_data->tex_y = (int)tex_data->tex_pos & (vars->map_data->tex_height - 1);
		tex_data->tex_pos += tex_data->step;
		if (ray->perp_wall_dist > VISIBLE_RANGE)
			return ;
		color = get_tex_color(y, tex_data, vars, ray);
		put_pixel(x, y, color, &vars->img);
		y++;
	}
}

static int	get_tex_color(int y, t_tex_data *tex_data, \
				t_vars *vars, t_ray *ray)
{
	float	relative_y;
	float	center_dist;
	float	radial_factor;
	int		texture_index;
	int		color;

	relative_y = (y - ray->draw_start) / (float)ray->line_height;
	center_dist = fabsf(relative_y - 0.5f) * 2.0f;
	radial_factor = 1.0 - 0.2 * (center_dist * center_dist);
	texture_index = vars->map_data->tex_height * tex_data->tex_y + tex_data->tex_x;
	color = vars->map_data->texture[tex_data->tex_num][texture_index];
	color = apply_opacity(color, tex_data->base_opacity * radial_factor);
	return (color);
}
