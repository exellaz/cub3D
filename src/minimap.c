/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:07:26 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/01/22 16:24:39 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#define VISIBLE_RANGE 4

int     apply_opacity(int color, float opacity);
void	draw_square(int x, int y, int size, int color, t_img *img);
void	draw_full_square(int x, int y, int size, int color, t_img *img);

void render_minimap(float px, float py, char **map, t_vars *vars) {
	int minimap_size = 360;
	int tile_size = minimap_size / (2 * VISIBLE_RANGE + 1);
	int map_width = 14;
	int map_height = 10;
	int start_x = floor(px) - VISIBLE_RANGE;
	int start_y = floor(py) - VISIBLE_RANGE;
	int	color;

	if (start_x < 0) {
		start_x = 0;
	} else if (start_x + 2 * VISIBLE_RANGE + 1 > map_width) {
		start_x = map_width - (2 * VISIBLE_RANGE + 1);
	}

	if (start_y < 0) {
		start_y = 0;
	} else if (start_y + 2 * VISIBLE_RANGE + 1 > map_height) {
		start_y = map_height - (2 * VISIBLE_RANGE + 1);
	}

	for (int y = start_y; y < start_y + 2 * VISIBLE_RANGE + 1; y++) {
		for (int x = start_x; x < start_x + 2 * VISIBLE_RANGE + 1; x++) {
			int screen_x = (x - start_x) * tile_size;
			int screen_y = (y - start_y) * tile_size;

			float distance = sqrt(pow(x - px, 2) + pow(y - py, 2));
			float opacity = fmax(0.0, 1.0 - (distance / VISIBLE_RANGE));

			if (map[y][x] == '1')
				color = 0x0000FF;
			else
				color = 0xFFFFFF;
			color = apply_opacity(color, opacity); // Apply fade-in effect

			draw_full_square(screen_x, screen_y, tile_size, color, &vars->img);
		}
	}

	int player_screen_x = (px - start_x) * tile_size;
	int player_screen_y = (py - start_y) * tile_size;
	draw_full_square(player_screen_x - tile_size / 4, player_screen_y - tile_size / 4, tile_size / 2, 0xFF0000, &vars->img);
}

int apply_opacity(int color, float opacity) {
	int r = ((color >> 16) & 0xFF) * opacity;
	int g = ((color >> 8) & 0xFF) * opacity;
	int b = (color & 0xFF) * opacity;
	return (r << 16) | (g << 8) | b;
}