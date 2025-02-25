/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/25 09:38:50 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_point map, int range, t_vars *vars);
static int		get_minimap_range(t_map *map_data);
static int		get_pixel_color(t_point tile, t_fpoint pixel, \
					char **map, t_vars *vars);
unsigned int	apply_opacity(unsigned int color, float opacity);

void	render_minimap(t_player *player, t_vars *vars, t_map *map_data)
{
	t_point	map;
	int		range;

	range = get_minimap_range(map_data);
	vars->tile_size = MINIMAP_SIZE / range;
	map.x = player->pos_x - (float)range / 2;
	if (map.x < 0)
		map.x = 0;
	else if (map.x + range > map_data->width)
		map.x = map_data->width - range;
	map.y = player->pos_y - (float)range / 2;
	if (map.y < 0)
		map.y = 0;
	else if (map.y + range > map_data->height)
		map.y = map_data->height - range;
	draw_border(0, 0, MINIMAP_SIZE, MINIMAP_OFFSET, 0x808080, &vars->img);
	draw_minimap(map, range, vars);
	draw_player(player, map.x, map.y, vars);
}

void	draw_minimap(t_point map, int range, t_vars *vars)
{
	t_point		screen;
	t_fpoint	pixel;
	t_point		tile;
	int			color;

	pixel.y = map.y * vars->tile_size;
	while (pixel.y < (map.y + range) * vars->tile_size)
	{
		pixel.x = map.x * vars->tile_size;
		while (pixel.x < (map.x + range) * vars->tile_size)
		{
			screen.x = (pixel.x - map.x * vars->tile_size) + MINIMAP_OFFSET;
			screen.y = (pixel.y - map.y * vars->tile_size) + MINIMAP_OFFSET;
			tile.x = pixel.x / vars->tile_size;
			tile.y = pixel.y / vars->tile_size;
			color = get_pixel_color(tile, pixel, vars->map_data->map, vars);
			put_pixel(screen.x, screen.y, color, &vars->img);
			pixel.x++;
		}
		pixel.y++;
	}
}

int	get_pixel_color(t_point tile, t_fpoint pixel, char **map, t_vars *vars)
{
	float	distance;
	float	opacity;
	int		color;
	int		tile_size;
	t_point	tex;

	tile_size = vars->tile_size;
	distance = sqrt(pow((pixel.x / tile_size) - vars->player->pos_x, 2) \
				+ pow((pixel.y / tile_size) - vars->player->pos_y, 2));
	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
	tex.x = ((int)pixel.x % tile_size * TEX_WIDTH) / tile_size;
	tex.y = ((int)pixel.y % tile_size * TEX_HEIGHT) / tile_size;
	if (map[tile.y][tile.x] == '1')
		color = vars->texture[0][tex.y * TEX_WIDTH + tex.x];
	else if (map[tile.y][tile.x] == 'D')
		color = 0xFF00FF;
	else
	{
		color = vars->texture[4][tex.y * TEX_WIDTH + tex.x];
		color = (color >> 1) & 8355711;
	}
	return (apply_opacity(color, opacity));
}

unsigned int	apply_opacity(unsigned int color, float opacity)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * opacity;
	g = ((color >> 8) & 0xFF) * opacity;
	b = (color & 0xFF) * opacity;
	return ((r << 16) | (g << 8) | b);
}

int	get_minimap_range(t_map *map_data)
{
	int	range_x;
	int	range_y;

	range_x = 2 * VISIBLE_RANGE + 1;
	range_y = 2 * VISIBLE_RANGE + 1;
	if (map_data->width < range_x)
		range_x = map_data->width;
	if (map_data->height < range_y)
		range_y = map_data->height;
	return (fmin(range_x, range_y));
}
