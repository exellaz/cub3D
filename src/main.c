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
int		draw_loop(t_vars *mlx);


int	main(int ac, char **av)
{
	void	*mlx;
	t_map	*map;
	int		fd;

	fd = validate_arg(ac, av[1]);
	mlx = mlx_init();
	map = parse_map(fd, mlx);
	printf("door texure path: %s\n", map->texture[4].path);
	for (int i = 0; i < map->door_count; i++)
	{
		printf("door %d: x: %d, y: %d, is_open: %d\n", i, map->door[i].x, map->door[i].y, map->door[i].is_open);
		free_img(map->texture[i].img, mlx);
	}
	mem_clean();
	return (0);
}

char	**hardcode_map(void)
{
	char **map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111111";
	map[1] = "10001000000001";
	map[2] = "10001000000001";
	map[3] = "10001000011111";
	map[4] = "10000100000001";
	map[5] = "10000100000001";
	map[6] = "10000000010001";
	map[7] = "10000000010001";
	map[8] = "10000000010001";
	map[9] = "11111111111111";
	map[10] = NULL;
	return (map);
}

void put_pixel(int x, int y, int color, t_img *img)
{
	if(x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return;

	int index = y * img->line_length + x * img->bits_per_pixel / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
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

int	draw_loop(t_vars *mlx)
{
	t_player	*player;

	player = mlx->player;
	frame_counter(mlx->fps);
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	handle_player_controls(mlx->map, player, mlx->fps);
	raycast(mlx);
	if (mlx->minimap_toggle == true)
		render_minimap(player, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}
