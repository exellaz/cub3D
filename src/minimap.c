/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/23 18:39:18 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_player *player, float map_x, float map_y, int range, t_vars *vars);
// static int		get_tile_color(t_player *player, int x, int y, char **map);
// int	get_pixel_color(t_player *player, int tile_x, int tile_y, float pixel_x, float pixel_y, char **map, float tile_size);
int	get_pixel_color(t_player *player, int tile_x, int tile_y, float pixel_x, float pixel_y, char **map, int tile_size, t_vars *vars);
static int		get_minimap_range(t_map *map_data);
unsigned int	apply_opacity(unsigned int color, float opacity);

void	render_minimap(t_player *player, t_vars *vars, t_map *map_data)
{
	float	map_x;
	float	map_y;
	int		range;

	range = get_minimap_range(map_data);
	vars->tile_size = MINIMAP_SIZE / range;

	map_x = player->pos_x - (float)range / 2;
	if (map_x < 0)
		map_x = 0;
	else if (map_x + range > map_data->width)
		map_x = map_data->width - range;
	map_y = player->pos_y - (float)range / 2;
	if (map_y < 0)
		map_y = 0;
	else if (map_y + range > map_data->height)
		map_y = map_data->height - range;
	draw_border(0, 0, MINIMAP_SIZE, MINIMAP_OFFSET, 0x808080, &vars->img);
	draw_minimap(player, map_x, map_y, range, vars);
	draw_player(player, map_x, map_y, vars);
}

void	draw_minimap(t_player *player, float map_x, float map_y, int range, t_vars *vars)
{
	int	color;
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	y = map_y * vars->tile_size;
	while (y < (map_y + range) * vars->tile_size)
	{
		x = map_x * vars->tile_size;
		while (x < (map_x + range) * vars->tile_size)
		{
			screen_x = (x - map_x * vars->tile_size) + MINIMAP_OFFSET;
			screen_y = (y - map_y * vars->tile_size) + MINIMAP_OFFSET;
			color = get_pixel_color(player, x / vars->tile_size, y / vars->tile_size, x, y, vars->map_data->map, vars->tile_size, vars);
			put_pixel(screen_x, screen_y, color, &vars->img);
			x++;
		}
		y++;
	}
}

int	get_pixel_color(t_player *player, int tile_x, int tile_y, float pixel_x, float pixel_y, char **map, int tile_size, t_vars *vars)
{
	float	distance;
	float	opacity;
	int		color;
	int		tex_x;
	int		tex_y;

	distance = sqrt(pow((pixel_x / tile_size) - player->pos_x, 2) + pow((pixel_y / tile_size) - player->pos_y, 2));
	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
	tex_x = ((int)pixel_x % tile_size * TEX_WIDTH) / tile_size;
	tex_y = ((int)pixel_y % tile_size * TEX_HEIGHT) / tile_size;
	if (map[tile_y][tile_x] == '1')
	{
		color = vars->texture[0][tex_y * TEX_WIDTH + tex_x];
	}
	else if (map[tile_y][tile_x] == 'D')
		color = 0xFF00FF;
	else
	{
		color = vars->texture[4][tex_y * TEX_WIDTH + tex_x];
		color = (color >> 1) & 8355711;
	}
	return (apply_opacity(color, opacity));
}

int	get_tile_color(t_player *player, int x, int y, char **map)
{
	float	distance;
	float	opacity;
	int		color;

	distance = sqrt(pow(x - player->pos_x, 2) + pow(y - player->pos_y, 2));
	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
	if (map[y][x] == '1')
		color = 0x0000FF;
	else if (map[y][x] == 'D')
		color = 0xFF00FF;
	else
		color = 0xFFFFFF;
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
