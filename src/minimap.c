/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/09 14:09:26 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_player *player, int map_x, int map_y, int range, t_vars *vars);
static void		draw_player(t_player *player, int map_x, int map_y, t_vars *vars);
static int		get_tile_color(t_player *player, int x, int y, char **map);
static int		get_size_and_range(t_vars *vars, t_map *map_data);
unsigned int	apply_opacity(unsigned int color, float opacity);

void	render_minimap(t_player *player, t_vars *vars, t_map *map_data)
{
	int	map_x;
	int	map_y;
	int	range;

	range = get_size_and_range(vars, map_data);
	map_x = ceil(player->pos_x) - VISIBLE_RANGE;
	if (map_x < 0)
		map_x = 0;
	else if (map_x + range > map_data->width)
		map_x = map_data->width - range;
	map_y = ceil(player->pos_y) - VISIBLE_RANGE;
	if (map_y < 0)
		map_y = 0;
	else if (map_y + range > map_data->height)
		map_y = map_data->height - range;
	draw_border(0, 0, MINIMAP_SIZE, MINIMAP_OFFSET, 0x808080, &vars->img);
	draw_minimap(player, map_x, map_y, range, vars);
	draw_player(player, map_x, map_y, vars);
}

static void	draw_player(t_player *player, int map_x, int map_y, t_vars *vars)
{
	int	player_screen_x;
	int	player_screen_y;
	int	tile_size;
	int	player_offset;

	tile_size = vars->tile_size;
	player_screen_x = (player->pos_x - map_x) * tile_size;
	player_screen_y = (player->pos_y - map_y) * tile_size;
	player_offset = tile_size / 4 - MINIMAP_OFFSET;
	draw_tile(player_screen_x - player_offset, player_screen_y - player_offset, \
				tile_size / 2, 0xFF0000, &vars->img);
}

void	draw_minimap(t_player *player, int map_x, int map_y, int range, t_vars *vars)
{
	int	color;
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	y = map_y;
	while (y < map_y + range)
	{
		x = map_x;
		while (x < map_x + range)
		{
			screen_x = (x - map_x) * vars->tile_size + MINIMAP_OFFSET;
			screen_y = (y - map_y) * vars->tile_size + MINIMAP_OFFSET;
			color = get_tile_color(player, x, y, vars->map_data->map);
			draw_tile(screen_x, screen_y, vars->tile_size, color, &vars->img);
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
	if (map[y][x] == '1' || map[y][x] == 'D')
		color = 0x0000FF;
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

int	get_size_and_range(t_vars *vars, t_map *map_data)
{
	int	range_x;
	int	range_y;

	range_x = 2 * VISIBLE_RANGE + 1;
	range_y = 2 * VISIBLE_RANGE + 1;
	if (map_data->width < range_x)
	{
		range_x = map_data->width;
		vars->tile_size = MINIMAP_SIZE / map_data->height;
	}
	if (map_data->height < range_y)
	{
		range_y = map_data->height;
		vars->tile_size = MINIMAP_SIZE / map_data->height;
	}
	return (fmin(range_x, range_y));
}