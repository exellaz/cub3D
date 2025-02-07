#include <time.h>
#include <math.h>

#include <mlx.h>

#include "graphics.h"
#include "events.h"
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

int	draw_loop(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	frame_counter(vars->fps);
	// ft_bzero(vars->img.addr, WIN_WIDTH * WIN_HEIGHT * (vars->img.bits_per_pixel / 8));
	handle_player_controls(vars->map, player, vars->fps, vars->doors);
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(x, y, 0x000000, &vars->img);
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(x, y, 0x000000, &vars->img);
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(x, y, 0x808080, &vars->img);
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(x, y, 0x808080, &vars->img);
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

void	put_pixel(int x, int y, int color, t_img *img)
{
	int	index;

	if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return;
	index = (y * (img->line_length / 4)) + x;
	((int *)img->addr)[index] = color;
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
