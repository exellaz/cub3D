#include "libmem.h"
#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

char	**get_map(void)
{
	char **map;

	// map = malloc(sizeof(char *) * 22);
	// map[0] = "111111111111111111111";
	// map[1] = "101000001000000000001";
	// map[2] = "101010101011111110001";
	// map[3] = "100010100010000010001";
	// map[4] = "111110101111101011101";
	// map[5] = "100000101000101000001";
	// map[6] = "101111101011101111111";
	// map[7] = "101000001010100000101";
	// map[8] = "101011111010111110101";
	// map[9] = "101010001010100010101";
	// map[10] = "101110101010101010101";
	// map[11] = "100000101010001010001";
	// map[12] = "111111101011111011101";
	// map[13] = "100000101000100010001";
	// map[14] = "101110101110101110111";
	// map[15] = "101000100000100010101";
	// map[16] = "101011111111111010101";
	// map[17] = "100010000000000010001";
	// map[18] = "101010111011111111101";
	// map[19] = "1N1000001000000000001";
	// map[20] = "111111111111111111111";
	// map[21] = NULL;
	map = malloc(sizeof(char *) * 11);
	map[0] = "1111111111";
	map[1] = "1000000001";
	map[2] = "1000000001";
	map[3] = "1000000001";
	map[4] = "1000000001";
	map[5] = "1000000001";
	map[6] = "1000000001";
	map[7] = "1000000001";
	map[8] = "1000000001";
	map[9] = "1111111111";
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
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, img);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, img);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, img);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, img);

	// int	draw_x;
	// int	draw_y;

	// draw_y = 0;
	// while (draw_y < size)
	// {
	// 	draw_x = 0;
	// 	while (draw_x < size)
	// 	{
	// 		put_pixel(x + draw_x, y + draw_y, color, img);
	// 		draw_x++;
	// 	}
	// 	draw_y++;
	// }
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
				draw_square(x * 64, y * 64, 64, color, &mlx->img);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_mlx	*mlx)
{
	t_player *player;

	player = mlx->player;
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	draw_square(player->x, player->y, 64, 0xFFFF00, &mlx->img);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac, (void)av;
	t_mlx		mlx;
	t_player	player;

	setup_mlx(&mlx, &player);
	mlx_loop_hook(mlx.mlx, &draw_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
