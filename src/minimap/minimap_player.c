/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:57:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/14 11:00:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void		draw_filled_triangle(t_fpoint v0, t_fpoint v1, \
					t_fpoint v2, t_img *img);
static int		point_in_triangle(t_fpoint point, t_fpoint v0, \
					t_fpoint v1, t_fpoint v2);
static float	sign(t_fpoint a, t_fpoint b, t_fpoint p);

void	draw_player(t_player *player, t_fpoint map, \
			t_map *map_data, t_vars *vars)
{
	float		size;
	float		angle;
	float		player_x;
	float		player_y;
	t_fpoint	points[3];

	size = map_data->tile_size * 0.6;
	angle = atan2(player->dir_y, player->dir_x);
	player_x = (player->pos_x - map.x) * map_data->tile_size + MINIMAP_OFFSET;
	player_y = (player->pos_y - map.y) * map_data->tile_size + MINIMAP_OFFSET;
	points[0].x = player_x + cos(angle) * (size / 2);
	points[0].y = player_y + sin(angle) * (size / 2);
	points[1].x = player_x + cos(angle + 2.5) * size * 0.6;
	points[1].y = player_y + sin(angle + 2.5) * size * 0.6;
	points[2].x = player_x + cos(angle - 2.5) * size * 0.6;
	points[2].y = player_y + sin(angle - 2.5) * size * 0.6;
	draw_filled_triangle(points[0], points[1], points[2], &vars->img);
}

static void	draw_filled_triangle(t_fpoint v0, t_fpoint v1, \
				t_fpoint v2, t_img *img)
{
	t_fpoint	min;
	t_fpoint	max;
	t_fpoint	point;

	min.x = fmin(fmin(v0.x, v1.x), v2.x);
	max.x = fmax(fmax(v0.x, v1.x), v2.x);
	min.y = fmin(fmin(v0.y, v1.y), v2.y);
	max.y = fmax(fmax(v0.y, v1.y), v2.y);
	point.y = min.y;
	while (point.y <= max.y)
	{
		point.x = min.x;
		while (point.x <= max.x)
		{
			if (point_in_triangle(point, v0, v1, v2))
				put_pixel(point.x, point.y, MARKER_COLOR, img);
			point.x++;
		}
		point.y++;
	}
}

static int	point_in_triangle(t_fpoint point, t_fpoint v0, \
				t_fpoint v1, t_fpoint v2)
{
	float	d1;
	float	d2;
	float	d3;
	int		has_neg;
	int		has_pos;

	d1 = sign(v0, v1, point);
	d2 = sign(v1, v2, point);
	d3 = sign(v2, v0, point);
	has_neg = (d1 < 0 || d2 < 0 || d3 < 0);
	has_pos = (d1 > 0 || d2 > 0 || d3 > 0);
	return (!(has_neg && has_pos));
}

static float	sign(t_fpoint a, t_fpoint b, t_fpoint p)
{
	return ((p.x - b.x) * (a.y - b.y) - (p.y - b.y) * (a.x - b.x));
}
