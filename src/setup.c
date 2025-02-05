/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:17 by we                #+#    #+#             */
/*   Updated: 2025/02/05 21:49:36 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "map.h"
#include "cub3D.h"
#include "utils.h"

char	**hardcode_map(void);

static void	init_textures(t_vars *vars)
{
	int	x;
	int	y;
	int	xycolor;
	(void)xycolor;

	vars->texture = malloc(sizeof(int *) * 2);
	vars->texture[0] = malloc(TEX_HEIGHT * TEX_WIDTH * sizeof(int));
	vars->texture[1] = malloc(TEX_HEIGHT * TEX_WIDTH * sizeof(int));
	// vars->texture[2] = malloc(TEX_HEIGHT * TEX_WIDTH * sizeof(int));
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
			vars->texture[1][TEX_WIDTH * y + x] = 0xFF0000;
			y++;
		}
		x++;
	}
}

static void	init_fps(t_vars *vars)
{
	t_fps	*fps;

	fps = ft_calloc(1, sizeof(t_fps));
	fps->frame_count = 0;
	fps->fps = 0.0;
	fps->start_time = clock();
	vars->fps = fps;
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
	printf("player->pos_x: %f\n", player->pos_x);
	printf("player->pos_y: %f\n", player->pos_y);
	// player->dir_x = 1;
	// player->dir_y = 0;
	// player->plane_x = 0;
	// player->plane_y = 0.66;
	init_player_dir(player, map_data->spawn[2]);
	printf("%c\n", map_data->spawn[2]);
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
	t_map	*map_data;

	map_data = parse_map(fd, vars->mlx);
	setup_mlx(vars);
	init_fps(vars);
	init_textures(vars);
	init_player(vars, map_data);
	// vars->map = hardcode_map();
	vars->map = lst_to_arr(map_data->map);
	vars->map_data = map_data;
	vars->map_width = map_data->width;
	vars->map_height = map_data->height;
	vars->tile_size = MINIMAP_SIZE / 9;
	// init_doors(vars->map, vars);
}
