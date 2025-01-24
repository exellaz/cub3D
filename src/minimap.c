/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/01/24 16:45:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int		apply_opacity(int color, float opacity);
void	draw_square(int x, int y, int size, int color, t_img *img);
void	draw_full_square(int x, int y, int size, int color, t_img *img);
void	draw_minimap(int px, int py, int start_x, int start_y, t_vars *vars);
void	draw_minimap_player(float px, float py, int start_x, int start_y, t_vars *vars);
int		get_tile_color(int x, int y, float px, float py, char **map);

void render_minimap(float px, float py, t_vars *vars)
{
	int	start_x;
	int	start_y;

	start_x = floor(px) - VISIBLE_RANGE;
	if (start_x < 0)
		start_x = 0;
	else if (start_x + 2 * VISIBLE_RANGE + 1 > vars->map_width)
		start_x = vars->map_width - (2 * VISIBLE_RANGE + 1);
	start_y = floor(py) - VISIBLE_RANGE;
	if (start_y < 0)
		start_y = 0;
	else if (start_y + 2 * VISIBLE_RANGE + 1 > vars->map_height)
		start_y = vars->map_height - (2 * VISIBLE_RANGE + 1);
	draw_minimap(px, py, start_x, start_y, vars);
	draw_minimap_player(px, py, start_x, start_y, vars);
}

void	draw_minimap_player(float px, float py, int start_x, int start_y, t_vars *vars)
{
	int player_screen_x;
	int player_screen_y;
	int	tile_size;
	int	player_offset;

	tile_size = vars->minimap_tile_size;
	player_screen_x = (px - start_x) * tile_size;
	player_screen_y = (py - start_y) * tile_size;
	player_offset = tile_size / 4;
	draw_full_square(player_screen_x - player_offset, player_screen_y - player_offset, tile_size / 2, 0xFF0000, &vars->img);
}

void	draw_minimap(int px, int py, int start_x, int start_y, t_vars *vars)
{
	int	color;
	int	screen_x;
	int	screen_y;
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + 2 * VISIBLE_RANGE + 1)
	{
		x = start_x;
		while (x < start_x + 2 * VISIBLE_RANGE + 1)
		{
			screen_x = (x - start_x) * vars->minimap_tile_size;
			screen_y = (y - start_y) * vars->minimap_tile_size;
			color = get_tile_color(x, y, px, py, vars->map);
			draw_full_square(screen_x, screen_y, vars->minimap_tile_size, color, &vars->img);
			x++;
		}
		y++;
	}
}

int	get_tile_color(int x, int y, float px, float py, char **map)
{
	float	distance;
	float	opacity;
	int		color;

	distance = sqrt(pow(x - px, 2) + pow(y - py, 2));
	opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));
	if (map[y][x] == '1')
		color = 0x0000FF;
	else
		color = 0xFFFFFF;
	return (apply_opacity(color, opacity));
}

int apply_opacity(int color, float opacity)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * opacity;
	g = ((color >> 8) & 0xFF) * opacity;
	b = (color & 0xFF) * opacity;
	return (r << 16) | (g << 8) | b;
}