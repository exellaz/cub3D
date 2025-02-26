/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/26 08:14:44 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_point map, int range, t_map *map_data, t_vars *vars);
static int		get_minimap_range(t_map *map_data);
static int		get_pixel_color(t_point tile, t_fpoint pixel, \
					t_map *map_data, t_player *player);
int				apply_opacity(int color, float opacity);

void	render_minimap(t_player *player, t_vars *vars, t_map *map_data)
{
	t_point	map;
	int		range;

	range = get_minimap_range(map_data);
	map_data->tile_size = MINIMAP_SIZE / range;
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
	draw_minimap(map, range, map_data, vars);
	draw_player(player, map.x, map.y, vars);
}

void	draw_minimap(t_point map, int range, t_map *map_data, t_vars *vars)
{
	t_point		screen;
	t_fpoint	pixel;
	t_point		tile;
	int			tile_size;
	int			color;

	tile_size = map_data->tile_size;
	pixel.y = map.y * tile_size;
	while (pixel.y < (map.y + range) * map_data->tile_size)
	{
		pixel.x = map.x * map_data->tile_size;
		while (pixel.x < (map.x + range) * map_data->tile_size)
		{
			screen.x = (pixel.x - map.x * tile_size) + MINIMAP_OFFSET;
			screen.y = (pixel.y - map.y * tile_size) + MINIMAP_OFFSET;
			tile.x = pixel.x / tile_size;
			tile.y = pixel.y / tile_size;
			color = get_pixel_color(tile, pixel, map_data, vars->player);
			put_pixel(screen.x, screen.y, color, &vars->img);
			pixel.x++;
		}
		pixel.y++;
	}
}

int	get_pixel_color(t_point tile, t_fpoint pixel, t_map *map_data, t_player *player)
{
	float	distance;
	float	opacity;
	int		color;
	int		tile_size;
	t_point	tex;

	tile_size = map_data->tile_size;
	distance = sqrt(pow((pixel.x / tile_size) - player->pos_x, 2) \
				+ pow((pixel.y / tile_size) - player->pos_y, 2));
	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
	tex.x = ((int)pixel.x % tile_size * map_data->tex_width) / tile_size;
	tex.y = ((int)pixel.y % tile_size * map_data->tex_height) / tile_size;
	if (map_data->map[tile.y][tile.x] == '1')
		color = map_data->texture[0][tex.y * map_data->tex_width + tex.x];
	else if (map_data->map[tile.y][tile.x] == 'D')
		color = map_data->texture[map_data->texture_count - 1][tex.y * map_data->tex_width + tex.x];
	else
	{
		if (map_data->texture_count < 6)
			color = map_data->floor_color;
		else
			color = map_data->texture[4][tex.y * map_data->tex_width + tex.x];
		color = (color >> 1) & 8355711;
	}
	return (apply_opacity(color, opacity));
}

int	apply_opacity(int color, float opacity)
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
