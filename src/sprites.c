/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:39 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/02/28 16:02:37 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(int x, int y, int color, t_img *img);

void	render_sprite(t_vars *vars)
{
	t_texture	texture;
	int			*frame;
	int			x;
	int			y;
	static int	frame_index = 0;

	if (vars->fps->frame_count % 10 == 0)
		frame_index++;
	if (frame_index == 7)
		frame_index = 0;
	texture = vars->sprite->frame_data[frame_index];
	frame = texture.img->addr;

	y = 0;
	x = 0;
	while (y < texture.height)
	{
		x = 0;
		while (x < texture.width)
		{
			if ((unsigned int)frame[y * texture.width + x] != 0xFF000000)
			{
				draw_square(x * SPRITE_SCALE, y * SPRITE_SCALE, frame[y * texture.width + x], &vars->img);
			}
			x++;
		}
		y++;
	}
}

void	draw_square(int x, int y, int color, t_img *img)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	start_x = x;
	start_y = y;
	end_x = start_x + SPRITE_SCALE;
	end_y = start_y + SPRITE_SCALE;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			put_pixel(x + TORCH_X, y + TORCH_Y, color, img);
			x++;
		}
		y++;
	}
}

void	init_torch_sprite(t_vars *vars)
{
	t_texture	*textures;

	vars->sprite = ft_calloc(1, sizeof(t_sprite));
	textures = vars->sprite->frame_data;
	textures[0].path = TORCH_1;
	textures[1].path = TORCH_2;
	textures[2].path = TORCH_3;
	textures[3].path = TORCH_4;
	textures[4].path = TORCH_5;
	textures[5].path = TORCH_6;
	textures[6].path = TORCH_7;
	load_textures(textures, vars->mlx);
}