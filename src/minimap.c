/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/22 15:33:19 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_player *player, float map_x, float map_y, int range, t_vars *vars);
static void		draw_player(t_player *player, float map_x, float map_y, int range, t_vars *vars);
static int		get_tile_color(t_player *player, int x, int y, char **map);
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
	draw_player(player, map_x, map_y, range, vars);
}

static void	draw_player(t_player *player, float map_x, float map_y, int range, t_vars *vars)
{
	int	player_screen_x;
	int	player_screen_y;
	int	tile_size;
	int	player_offset;
	float	offset_x;
	float	offset_y;

	tile_size = vars->tile_size;
	player_offset = tile_size / 4;

	offset_x = (player->pos_x - map_x) * tile_size;
	offset_y = (player->pos_y - map_y) * tile_size;

	if (map_x == 0)
		player_screen_x = offset_x + MINIMAP_OFFSET;
	else if (map_x + range >= vars->map_data->width)
		player_screen_x = MINIMAP_SIZE - ((vars->map_data->width - player->pos_x) * tile_size) + MINIMAP_OFFSET;
	else
		player_screen_x = MINIMAP_SIZE / 2 + (offset_x - (range * tile_size) / 2) + MINIMAP_OFFSET;

	if (map_y == 0)
		player_screen_y = offset_y + MINIMAP_OFFSET;
	else if (map_y + range >= vars->map_data->height)
		player_screen_y = MINIMAP_SIZE - ((vars->map_data->height - player->pos_y) * tile_size) + MINIMAP_OFFSET;
	else
		player_screen_y = MINIMAP_SIZE / 2 + (offset_y - (range * tile_size) / 2) + MINIMAP_OFFSET;

	draw_tile(player_screen_x - player_offset, player_screen_y - player_offset,
			tile_size / 2, 0xFF0000, &vars->img);
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
			color = get_tile_color(player, x / vars->tile_size, y / vars->tile_size, vars->map_data->map);
			put_pixel(screen_x, screen_y, color, &vars->img);
			x++;
		}
		y++;
	}
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
