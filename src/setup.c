/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/02/26 08:14:19 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "map.h"
#include "cub3D.h"
#include "utils.h"

void	init_fps(t_vars *vars);

static void	init_textures(t_vars *vars, t_map *map, int tex_width, int tex_height)
{
	int	x;
	int	y;
	int	i;
	int j;
	int	tex_i;

	(void)vars;
	map->texture = mem_alloc(sizeof(int *) * map->texture_count);
	x = -1;
	while (++x < map->texture_count)
		map->texture[x] = mem_alloc(sizeof(int) * tex_height * tex_width);
	y = -1;
	while (++y < tex_height)
	{
		x = -1;
		while (++x < tex_width)
		{
			j = -1;
			i = -1;
			while (++i < 7)
			{
				if (!map->texture_data[i].path)
					continue ;
				tex_i = y * tex_width + x;
				map->texture[++j][tex_i] = (int)(map->texture_data[i].img->addr[tex_i]);
			}
		}
	}
}

static void	init_player_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
}

static void	init_player(t_vars *vars, t_map *map_data)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	player->pos_x = map_data->spawn[1];
	player->pos_y = map_data->spawn[0];
	init_player_dir(player, map_data->spawn[2]);
	vars->player = player;
}

static void	setup_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	vars->img.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->img.addr = (int *)mlx_get_data_addr(vars->img.img, \
		&vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	mlx_mouse_hide(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, DESTROY_NOTIFY, NOT_EVENT_MASK, quit, vars);
	mlx_hook(vars->win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, vars);
	mlx_hook(vars->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, vars);
	mlx_hook(vars->win, MOTION_NOTIFY, POINTER_MOTION_MASK, mouse_hook, vars);
}

void	init_vars(t_vars *vars, int fd)
{
	// ft_bzero(vars, sizeof(vars));
	vars->minimap_toggle = false;
	setup_mlx(vars);
	vars->map_data = parse_map(fd, vars->mlx);
	init_fps(vars);
	init_textures(vars, vars->map_data, vars->map_data->tex_width, vars->map_data->tex_height);
	init_player(vars, vars->map_data);
	vars->tile_size = MINIMAP_SIZE / (2 * VISIBLE_RANGE + 1);
}
