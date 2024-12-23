/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2024/12/23 11:53:56 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

void	setup_mlx(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, 800, 600, "Hello world!");
	mlx_hook(m->win, DESTROY_NOTIFY, NOT_EVENT_MASK, quit, m);
	mlx_hook(m->win, KEY_PRESS, KEY_PRESS_MASK, key_hook, m);
}
