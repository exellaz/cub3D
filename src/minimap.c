/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/22 21:23:29 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void		draw_minimap(t_player *player, float map_x, float map_y, int range, t_vars *vars);
static void		draw_player(t_player *player, float map_x, float map_y, t_vars *vars);
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

// static void	draw_player(t_player *player, float map_x, float map_y, int range, t_vars *vars)
// {
// 	int	player_screen_x;
// 	int	player_screen_y;
// 	int	tile_size;
// 	int	player_offset;
// 	float	offset_x;
// 	float	offset_y;

// 	tile_size = vars->tile_size;
// 	player_offset = tile_size / 4;

// 	offset_x = (player->pos_x - map_x) * tile_size;
// 	offset_y = (player->pos_y - map_y) * tile_size;

// 	if (map_x == 0)
// 		player_screen_x = offset_x + MINIMAP_OFFSET;
// 	else if (map_x + range >= vars->map_data->width)
// 		player_screen_x = MINIMAP_SIZE - ((vars->map_data->width - player->pos_x) * tile_size) + MINIMAP_OFFSET;
// 	else
// 		player_screen_x = MINIMAP_SIZE / 2 + (offset_x - (range * tile_size) / 2) + MINIMAP_OFFSET;

// 	if (map_y == 0)
// 		player_screen_y = offset_y + MINIMAP_OFFSET;
// 	else if (map_y + range >= vars->map_data->height)
// 		player_screen_y = MINIMAP_SIZE - ((vars->map_data->height - player->pos_y) * tile_size) + MINIMAP_OFFSET;
// 	else
// 		player_screen_y = MINIMAP_SIZE / 2 + (offset_y - (range * tile_size) / 2) + MINIMAP_OFFSET;

// 	draw_tile(player_screen_x - player_offset, player_screen_y - player_offset,
// 			tile_size / 2, 0xFF0000, &vars->img);
// }

static float	sign(float x1, float y1, float x2, float y2, float px, float py)
{
	return (px - x2) * (y1 - y2) - (py - y2) * (x1 - x2);
}

static int	point_in_triangle(float px, float py, float v0[2], float v1[2], float v2[2])
{
	float	d1, d2, d3;
	int		has_neg, has_pos;

	d1 = sign(px, py, v0[0], v0[1], v1[0], v1[1]);
	d2 = sign(px, py, v1[0], v1[1], v2[0], v2[1]);
	d3 = sign(px, py, v2[0], v2[1], v0[0], v0[1]);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

 void	draw_filled_triangle(float v0[2], float v1[2], float v2[2], int color, t_img *img)
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
	int	x;
	int	y;

	min_x = fmin(fmin(v0[0], v1[0]), v2[0]);
	max_x = fmax(fmax(v0[0], v1[0]), v2[0]);
	min_y = fmin(fmin(v0[1], v1[1]), v2[1]);
	max_y = fmax(fmax(v0[1], v1[1]), v2[1]);

	for (y = min_y; y <= max_y; y++)
	{
		for (x = min_x; x <= max_x; x++)
		{
			if (point_in_triangle(x, y, v0, v1, v2))
				put_pixel(x, y, color, img);
		}
	}
}

void	draw_line(int x0, int y0, int x1, int y1, int color, t_img *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;

	while (x0 != x1 || y0 != y1)
	{
		put_pixel(x0, y0, color, img);
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	draw_player(t_player *player, float map_x, float map_y, t_vars *vars)
{
	int		tile_size;
	float	player_screen_x;
	float	player_screen_y;
	float	angle;
	float	size;
	float	points[3][2];

	tile_size = vars->tile_size;
	size = tile_size * 0.6;

	player_screen_x = (player->pos_x - map_x) * tile_size + MINIMAP_OFFSET;
	player_screen_y = (player->pos_y - map_y) * tile_size + MINIMAP_OFFSET;

	angle = atan2(player->dir_y, player->dir_x);

	points[0][0] = player_screen_x + cos(angle) * (size / 2);
	points[0][1] = player_screen_y + sin(angle) * (size / 2);

	points[1][0] = player_screen_x + cos(angle + 2.5) * size * 0.6;
	points[1][1] = player_screen_y + sin(angle + 2.5) * size * 0.6;

	points[2][0] = player_screen_x + cos(angle - 2.5) * size * 0.6;
	points[2][1] = player_screen_y + sin(angle - 2.5) * size * 0.6;

	draw_filled_triangle(points[0], points[1], points[2], 0xFF0000, &vars->img);
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

// int	get_pixel_color(t_player *player, int tile_x, int tile_y, float pixel_x, float pixel_y, char **map, float tile_size)
// {
// 	float	distance;
// 	float	opacity;
// 	int		color;

// 	// Distance is calculated per pixel instead of per tile
// 	distance = sqrt(pow((pixel_x / tile_size) - player->pos_x, 2) + pow((pixel_y / tile_size) - player->pos_y, 2));
// 	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));

// 	// Get base tile color
// 	if (map[tile_y][tile_x] == '1')
// 		color = 0x0000FF;
// 	else if (map[tile_y][tile_x] == 'D')
// 		color = 0xFF00FF;
// 	else
// 		color = 0xFFFFFF;

// 	return (apply_opacity(color, opacity));
// }

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
