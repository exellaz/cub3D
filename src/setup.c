/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/01/10 19:22:25 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

void	setup_mlx(t_mlx *m, t_player *player)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	m->img.img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img.addr = mlx_get_data_addr(m->img.img, &m->img.bits_per_pixel, &m->img.line_length, &m->img.endian);
	player->pos_x = 3;
	player->pos_y = 3;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	m->player = player;
	m->map = get_map();
	mlx_put_image_to_window(m->mlx, m->win, m->img.img, 0, 0);
	mlx_hook(m->win, DESTROY_NOTIFY, NOT_EVENT_MASK, quit, m);
	mlx_hook(m->win, KEY_PRESS, KEY_PRESS_MASK, key_hook, m);
}
