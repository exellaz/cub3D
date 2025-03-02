/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcaster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:40:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/02 19:19:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_pixel(t_map *map_data, int opacity, int texture_index, t_img *img, t_point window);
void	draw_ceiling_pixel(t_map *map_data, int opacity, int texture_index, t_img *img, t_point window);

void	floor_casting(t_vars *vars)
{
	t_point		window;
	t_player	*player;
	t_map		*map_data;
	int			tex_width;
	int			tex_height;

	player = vars->player;
	map_data = vars->map_data;
	tex_width = map_data->tex_width;
	tex_height = map_data->tex_height;

	t_fpoint	ray_dir_0;
	t_fpoint	ray_dir_1;
	float		pos_z;

	ray_dir_0.x = player->dir_x - player->plane_x;
	ray_dir_0.y = player->dir_y - player->plane_y;
	ray_dir_1.x = player->dir_x + player->plane_x;
	ray_dir_1.y = player->dir_y + player->plane_y;

	pos_z = 0.5f * WIN_HEIGHT;

	window.y = WIN_HEIGHT / 2;
	while (window.y < WIN_HEIGHT)
	{
		int		p;
		int		opacity;
		float	row_distance;

		t_fpoint	floor;
		t_fpoint	floor_step;

		p = window.y - WIN_HEIGHT / 2;
		row_distance = pos_z / p;

		floor_step.x = row_distance * (ray_dir_1.x - ray_dir_0.x) / WIN_WIDTH;
		floor_step.y = row_distance * (ray_dir_1.y - ray_dir_0.y) / WIN_WIDTH;

		floor.x = player->pos_x + row_distance * ray_dir_0.x;
		floor.y = player->pos_y + row_distance * ray_dir_0.y;

		opacity = fmaxf(0.0f, 1.0f - (row_distance / (VISIBLE_RANGE))) * 255 * vars->max_brightness;

		window.x = 0;
		while (window.x < WIN_WIDTH)
		{
			t_point	cell;
			t_point	tex_coord;

			cell.x = (int)floor.x;
			cell.y = (int)floor.y;
			tex_coord.x = (int)(tex_width * (floor.x - cell.x)) & (tex_width - 1);
			tex_coord.y = (int)(tex_height * (floor.y - cell.y)) & (tex_height - 1);
			floor.x += floor_step.x;
			floor.y += floor_step.y;
			draw_floor_pixel(map_data, opacity, tex_width * tex_coord.y + tex_coord.x, &vars->img, window);
			draw_ceiling_pixel(map_data, opacity, tex_width * tex_coord.y + tex_coord.x, &vars->img, window);
			window.x++;
		}
		window.y++;
	}
}

void	draw_floor_pixel(t_map *map_data, int opacity, int texture_index, t_img *img, t_point window)
{
	int	color;

	if (map_data->texture_count < 6)
		color = map_data->floor_color;
	else
		color = map_data->texture[FLOOR][texture_index];
	color = apply_opacity(color, opacity);
	put_pixel(window.x, window.y, color, img);
}

void	draw_ceiling_pixel(t_map *map_data, int opacity, int texture_index, t_img *img, t_point window)
{
	int	color;

	if (map_data->texture_count < 6)
		color = map_data->ceiling_color;
	else
		color = map_data->texture[CEILING][texture_index];
	color = (color >> 1) & 8355711;
	color = apply_opacity(color, opacity);
	put_pixel(window.x, WIN_HEIGHT - window.y - 1, color, img);
}