/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:57:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/23 18:34:32 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static float	sign(t_point a, t_point b, t_point p)
{
	return ((p.x - b.x) * (a.y - b.y) - (p.y - b.y) * (a.x - b.x));
}

static int	point_in_triangle(t_point point, t_point v0, t_point v1, t_point v2)
{
	float	d1;
	float	d2;
	float	d3;
	int		has_neg;
	int		has_pos;

	d1 = sign(v0, v1, point);
	d2 = sign(v1, v2, point);
	d3 = sign(v2, v0, point);
	has_neg = d1 < 0 || d2 < 0 || d3 < 0;
	has_pos = d1 > 0 || d2 > 0 || d3 > 0;
	return (!(has_neg && has_pos));
}

void	draw_filled_triangle(t_point v0, t_point v1, t_point v2, t_img *img)
{
	t_point	min;
	t_point	max;
	t_point	point;

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
				put_pixel(point.x, point.y, CURSOR_COLOR, img);
			point.x++;
		}
		point.y++;
	}
}

void	draw_player(t_player *player, float map_x, float map_y, t_vars *vars)
{
	float	size;
	float	angle;
	float	player_x;
	float	player_y;
	t_point	points[3];

	size = vars->tile_size * 0.6;
	angle = atan2(player->dir_y, player->dir_x);
	player_x = (player->pos_x - map_x) * vars->tile_size + MINIMAP_OFFSET;
	player_y = (player->pos_y - map_y) * vars->tile_size + MINIMAP_OFFSET;
	points[0].x = player_x + cos(angle) * (size / 2);
	points[0].y = player_y + sin(angle) * (size / 2);
	points[1].x = player_x + cos(angle + 2.5) * size * 0.6;
	points[1].y = player_y + sin(angle + 2.5) * size * 0.6;
	points[2].x = player_x + cos(angle - 2.5) * size * 0.6;
	points[2].y = player_y + sin(angle - 2.5) * size * 0.6;
	draw_filled_triangle(points[0], points[1], points[2], &vars->img);
}
