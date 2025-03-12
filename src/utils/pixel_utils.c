/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:22:49 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 10:04:47 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(int x, int y, int color, t_img *img)
{
	int	index;

	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * img->line_length / 4) + x;
	((int *)img->addr)[index] = color;
}

int	apply_opacity(int color, int opacity_int)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (r * opacity_int) >> 8;
	g = (g * opacity_int) >> 8;
	b = (b * opacity_int) >> 8;
	return ((r << 16) | (g << 8) | b);
}
