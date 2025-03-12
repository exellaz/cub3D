/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:39 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 09:51:10 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "error.h"

static void	draw_scaled_pixel(int x, int y, int color, t_img *img);
static void	get_bobbing_offsets(t_player *player, t_fps *fps, t_sprite *sprite);
static int	get_frame_index(t_fps *fps, t_sprite *sprite);

void	render_sprite(t_vars *vars, t_sprite *sprite)
{
	t_texture		texture;
	unsigned int	*current_frame;
	int				frame_index;
	int				x;
	int				y;

	frame_index = get_frame_index(vars->fps, sprite);
	get_bobbing_offsets(vars->player, vars->fps, sprite);
	texture = sprite->frame_data[frame_index];
	current_frame = (unsigned int *)texture.img->addr;
	y = -1;
	while (++y < texture.height)
	{
		x = -1;
		while (++x < texture.width)
		{
			if (current_frame[y * texture.width + x] != 0xFF000000)
			{
				draw_scaled_pixel(x * SPRITE_SCALE + sprite->sway_offset,
					y * SPRITE_SCALE + sprite->bob_offset,
					current_frame[y * texture.width + x], &vars->img);
			}
		}
	}
}

static void	draw_scaled_pixel(int x, int y, int color, t_img *img)
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
			put_pixel(x + TORCH_1_X, y + TORCH_1_Y, color, img);
			x++;
		}
		y++;
	}
}

static void	get_bobbing_offsets(t_player *player, t_fps *fps, t_sprite *sprite)
{
	static float	bob_time = 0.0f;
	float			frame_time;

	frame_time = fps->frame_time;
	if (player->is_moving == true)
	{
		bob_time += frame_time * BOB_SPEED;
		sprite->bob_offset = sinf(bob_time) * (BOB_SPEED + frame_time);
		sprite->sway_offset = cosf(bob_time * 0.5f) * BOB_SPEED;
	}
}

static int	get_frame_index(t_fps *fps, t_sprite *sprite)
{
	static float	animation_time = 0.0f;
	static int		frame_index = 0;

	animation_time += fps->frame_time;
	if (animation_time >= sprite->frame_duration)
	{
		frame_index = (frame_index + 1) % SPRITE_1_FRAME_COUNT;
		animation_time = 0.0f;
	}
	return (frame_index);
}
