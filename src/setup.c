/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/02/09 13:12:49 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "map.h"
#include "cub3D.h"
#include "utils.h"

void	init_fps(t_vars *vars);

static void	init_textures(t_vars *vars, t_map *map)
{
	int	x;
	int	y;
	int	tex_index;

	(void)map;
	vars->texture = mem_alloc(sizeof(int *) * 5);
	x = -1;
	while (++x < 5)
		vars->texture[x] = mem_alloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			tex_index = y * TEX_WIDTH + x;
			vars->texture[0][tex_index] = map->texture[0].img->addr[tex_index];
			vars->texture[1][tex_index] = map->texture[1].img->addr[tex_index];
			vars->texture[2][tex_index] = map->texture[2].img->addr[tex_index];
			vars->texture[3][tex_index] = map->texture[3].img->addr[tex_index];
			vars->texture[4][tex_index] = map->texture[4].img->addr[tex_index];
			// vars->texture[0][tex_index] = 0xFFFFFF;
			// vars->texture[1][tex_index] = 0xFFFFFF;
			// vars->texture[2][tex_index] = 0xFFFFFF;
			// vars->texture[3][tex_index] = 0xFFFFFF;
			// vars->texture[4][tex_index] = 0xFF0000;
			x++;
		}
		y++;
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

void	init_doors(char **map, t_vars *vars)
{
	t_door	*doors;

	(void)map;
	doors = malloc(sizeof(t_door) * 4);
	doors[0].x = 4;
	doors[0].y = 2;
	doors[0].is_open = false;
	doors[1].x = -1;
	doors[1].y = -1;
	doors[0].is_open = false;
	vars->doors = doors;
}

void	init_vars(t_vars *vars, int fd)
{
	setup_mlx(vars);
	vars->map_data = parse_map(fd, vars->mlx);
	init_fps(vars);
	init_textures(vars, vars->map_data);
	init_player(vars, vars->map_data);
	vars->map = lst_to_arr(vars->map_data->map_list);
	vars->tile_size = MINIMAP_SIZE / (2 * VISIBLE_RANGE + 1);
	// init_doors(vars->map, vars);
}
