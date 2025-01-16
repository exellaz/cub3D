/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/01/16 09:45:14 by tjun-yu          ###   ########.fr       */
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
	player->x = 2 * 64;
	player->y = 2 * 64;
	player->angle = PI / 2;
	m->player = player;
	m->map = hardcode_map();
	mlx_put_image_to_window(m->mlx, m->win, m->img.img, 0, 0);
	mlx_hook(m->win, DESTROY_NOTIFY, NOT_EVENT_MASK, quit, m);
	mlx_hook(m->win, KEY_PRESS, KEY_PRESS_MASK, key_hook, m);
}
