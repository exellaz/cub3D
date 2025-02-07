#include <time.h>
#include <math.h>

#include <mlx.h>

#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "utils.h"
#include "map.h"
#include "cub3D.h"

void	raycast(t_vars *mlx);
void	draw_line(t_point start, t_point end, int color, t_img *img);
int		draw_loop(t_vars *vars);


int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = validate_arg(ac, av[1]);
	init_vars(&vars, fd);
	// print_map(map->map);
	mlx_loop_hook(vars.mlx, &draw_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

char	**hardcode_map(void)
{
	char **map;

	map = malloc(sizeof(char *) * 11);
	map[0] = ft_strdup("11111111111111");
	map[1] = ft_strdup("10001000000001");
	map[2] = ft_strdup("10002000000001");
	map[3] = ft_strdup("10001000011111");
	map[4] = ft_strdup("10000100000001");
	map[5] = ft_strdup("10000100000001");
	map[6] = ft_strdup("10000000010001");
	map[7] = ft_strdup("10000000010001");
	map[8] = ft_strdup("10000000010001");
	map[9] = ft_strdup("11111111111111");
	map[10] = NULL;
	return (map);
}

void put_pixel(int x, int y, int color, t_img *img)
{
	if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return;

	int index = (y * img->line_length / 4) + x;
	img->addr[index] = color;
	img->addr[index + 1] = (color >> 8);
	img->addr[index + 2] = (color >> 16);
}

void	draw_square(int x, int y, int size, int color, t_img *img)
{
	int	draw_x;
	int	draw_y;

	draw_y = 0;
	while (draw_y < size)
	{
		draw_x = 0;
		if (draw_y == 0 || draw_y == size - 1)
		{
			while (draw_x < size)
			{
				put_pixel(x + draw_x, y + draw_y, color, img);
				draw_x++;
			}
		}
		else
		{
			put_pixel(x, y + draw_y, color, img);
			put_pixel(x + size - 1, y + draw_y, color, img);
		}
		draw_y++;
	}
}

void	draw_tile(int x, int y, int size, int color, t_img *img)
{
	int	draw_x;
	int	draw_y;

	draw_y = 0;
	while (draw_y < size)
	{
		draw_x = 0;
		while (draw_x < size)
		{
			put_pixel(x + draw_x, y + draw_y, color, img);
			draw_x++;
		}
		draw_y++;
	}
}

void	draw_border(int x, int y, int size, int border_thickness, int border_color, t_img *img)
{
	int	draw_x;
	int	draw_y;
	int	border_end;

	border_end = size + (border_thickness * 2);
	draw_y = 0;
	while (draw_y < border_end)
	{
		draw_x = 0;
		while (draw_x < border_end)
		{
			if (draw_y < border_thickness || draw_y >= size || draw_x < border_thickness || draw_x >= size)
				put_pixel(x + draw_x, y + draw_y, border_color, img);
			draw_x++;
		}
		draw_y++;
	}
}

void	draw_map(t_vars *mlx)
{
	char	**map;
	int		color;
	int		x;
	int		y;

	map = mlx->map;
	color = 0x0000FF;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, color, &mlx->img);
			else
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, 0x808080, &mlx->img);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	frame_counter(vars->fps);
	ft_bzero(vars->img.addr, WIN_WIDTH * WIN_HEIGHT * (vars->img.bits_per_pixel / 8));
	handle_player_controls(vars->map, player, vars->fps, vars->doors);
	raycast(vars);
	// if (vars->doors[0].is_open == true)
	// 	vars->map[vars->doors[0].y][vars->doors[0].x] = '0';
	// else if (vars->doors[0].is_open == false)
	// 	vars->map[vars->doors[0].y][vars->doors[0].x] = '2';
	if (vars->minimap_toggle == true)
		render_minimap(player, vars, vars->map_data);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
