#include "libmem.h"
#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

char	**get_map(void)
{
	char **map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111111";
	map[1] = "10000000000001";
	map[2] = "10000000000001";
	map[3] = "10000000000001";
	map[4] = "10000000000001";
	map[5] = "10000000000001";
	map[6] = "10000000000001";
	map[7] = "10000000000001";
	map[8] = "10000000000001";
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
				draw_square(x * 64, y * 64, 64, color, &mlx->img);
			x++;
		}
		y++;
	}
}

bool	ray_collision(float px, float py, t_mlx *mlx)
{
	int	x = px / 64;
	int y = py / 64;

	if (x < 0 || y < 0 || x >= WIN_WIDTH / 64 || y >= WIN_HEIGHT / 64)
		return (true);
	if (y < 10 && x < 14 && mlx->map[y][x] == '1') // Change 10 and 14 to width and height of map
		return (true);
	return (false);
}

int	draw_ray(t_player *player, t_mlx *mlx, float start_x)
{
	float	ray_x = player->x + 32;
	float	ray_y = player->y + 32;
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	while (!ray_collision(ray_x, ray_y, mlx))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, &mlx->img);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	return (0);
}

int	draw_loop(t_mlx	*mlx)
{
	t_player *player;

	player = mlx->player;
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	draw_map(mlx);

	float	fraction = PI / 3 / WIN_WIDTH;
	float	start_x = player->angle - PI / 6;
	int		i = 0;
	while (i < WIN_WIDTH)
	{
		draw_ray(player, mlx, start_x);
		start_x += fraction;
		i++;
	}
	draw_square(player->x, player->y, 64, 0xFFFF00, &mlx->img);
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
