/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:50:59 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 13:11:02 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

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

int	calculate_opacity(int tile_size, t_fpoint pixel, t_player *player)
{
	float	distance;
	int		opacity;

	distance = sqrtf(powf((pixel.x / tile_size) - player->pos_x, 2) \
				+ powf((pixel.y / tile_size) - player->pos_y, 2));
	opacity = fmaxf(0.0f, 1.0f - (distance / VISIBLE_RANGE)) * 255;
	return (opacity);
}

int	*get_tile_texture(t_point tile, char **map, int tex_count, int **textures)
{
	int	*texture;

	if (map[tile.y][tile.x] == '1')
		texture = textures[0];
	else if (map[tile.y][tile.x] == 'D')
		texture = textures[tex_count - 1];
	else
	{
		if (tex_count < 6)
			texture = NULL;
		else
			texture = textures[4];
	}
	return (texture);
}
