#include "libmem.h"
#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"
#include <time.h>

int	frame_counter(t_fps *fps);

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

bool	ray_collision(float px, float py, t_mlx *mlx)
{
	int	x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;

	if (x < 0 || y < 0 || x >= WIN_WIDTH / BLOCK_SIZE || y >= WIN_HEIGHT / BLOCK_SIZE + 1)
		return (true);
	if (y < 10 && x < 14 && mlx->map[y][x] == '1') // Change 10 and 14 to width and height of map
		return (true);
	return (false);
}

float	distance(float x, float y) // Calculates the distance with a fish-eye distortion
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_player *player)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - player->angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

int	draw_ray(t_player *player, t_mlx *mlx, float start_x, int i)
{
	float	ray_x = player->x + 16;
	float	ray_y = player->y + 16;
	float	cos_angle = cos(start_x);
	float	sin_angle = sin(start_x);
	(void)i;
	while (!ray_collision(ray_x, ray_y, mlx))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, &mlx->img);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	// float	dist = distance(ray_x - player->x, ray_y - player->y); // has fish-eye distortion
	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, player);
	float	height = (BLOCK_SIZE / dist) * (WIN_WIDTH / 2);
	int		start_y = (WIN_HEIGHT - height) / 2;
	int		end = start_y + height;
	while (start_y < end)
	{
		// put_pixel(i, start_y, 255, &mlx->img);
		start_y++;
	}
	return (0);
}

int	draw_loop(t_mlx	*mlx)
{
	t_player *player;

	frame_counter(mlx->fps);

	player = mlx->player;
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	draw_map(mlx);
	float	fraction = (PI / 3 / WIN_WIDTH);
	float	start_x = player->angle - PI / 6;
	int		i = 0;
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
