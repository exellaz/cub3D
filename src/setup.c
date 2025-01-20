/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/01/20 20:46:16 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

static void	init_textures(t_vars *vars)
{
	int	x;
	int	y;
	int	xycolor;
	(void)xycolor;

	vars->texture = malloc(sizeof(int *) * 1);
	vars->texture[0] = malloc(TEX_HEIGHT * TEX_WIDTH * sizeof(int));
	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			// vars->texture[0][TEX_WIDTH * y + x] = xycolor + 256
			// 	* xycolor + 65536 * xycolor;
			vars->texture[0][TEX_WIDTH * y + x] = 0xFFFFFF;
			y++;
		}
		x++;
	}
}

static void	init_fps(t_vars *vars)
{
	t_fps	*fps;

	fps = malloc(sizeof(t_fps));
	fps->frame_count = 0;
	fps->fps = 0.0;
	fps->start_time = clock();
	vars->fps = fps;
}

static void	init_player(t_vars *vars)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->pos_x = 3;
	player->pos_y = 3;
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	vars->player = player;
}

static void	setup_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, DESTROY_NOTIFY, NOT_EVENT_MASK, quit, vars);
	mlx_hook(vars->win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, vars);
	mlx_hook(vars->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, vars);
}

void	init_vars(t_vars *vars)
{
	init_textures(vars);
	init_player(vars);
	init_fps(vars);
	setup_mlx(vars);
	vars->map = get_map();
	vars->keys = ft_calloc(256, sizeof(bool));
}
