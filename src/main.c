#include "libmem.h"
#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"
#include <time.h>

char	**get_map(void)
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

void	draw_map(t_mlx *mlx)
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

int	draw_loop(t_mlx	*mlx)
{
	t_player *player;
	float	fraction;
	float	start_x;
	int		i;

	player = mlx->player;
	fraction = (PI / 3 / WIN_WIDTH);
	start_x = player->angle - PI / 6;
	frame_counter(mlx->fps);
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	draw_map(mlx);
	i = 0;
	while (i < WIN_WIDTH)
	{
		draw_ray(player, mlx, start_x, i);
		start_x += fraction;
		i++;
	}
	draw_square(player->x, player->y, 32, 0xFFFF00, &mlx->img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac, (void)av;
	t_mlx		mlx;
	t_player	player;
	t_fps		fps;

	fps.frame_count = 0;
	fps.fps = 0.0;
	fps.start_time = clock();

	mlx.fps = &fps;
	setup_mlx(&mlx, &player);
	mlx_loop_hook(mlx.mlx, &draw_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
