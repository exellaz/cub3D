#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"
#include <time.h>

#include <math.h>

void draw_line(t_point start, t_point end, int color, t_img *img)
{
	int dx = fabs(end.x - start.x);
	int dy = fabs(end.y - start.y);
	int sx = (start.x < end.x) ? 1 : -1;
	int sy = (start.y < end.y) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		put_pixel(start.x, start.y, color, img);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

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

// int	draw_loop(t_mlx	*mlx)
// {
// 	t_player *player;
// 	float	fraction;
// 	float	start_x;
// 	int		i;

// 	player = mlx->player;
// 	fraction = (PI / 3 / WIN_WIDTH);
// 	// start_x = player->angle - PI / 6;
// 	frame_counter(mlx->fps);
// 	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
// 	draw_map(mlx); // Draw Map in 2D
// 	i = 0;
// 	while (i < WIN_WIDTH)
// 	{
// 		draw_ray(player, mlx, start_x, i);
// 		start_x += fraction;
// 		i++;
// 	}
// 	draw_square(player->x, player->y, 32, 0xFFFF00, &mlx->img); // Draw Player in 2D
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
// 	return (0);
// }

int	new_draw_loop(t_mlx	*mlx)
{
	t_player *player;

	frame_counter(mlx->fps);
	ft_bzero(mlx->img.addr, WIN_WIDTH * WIN_HEIGHT * (mlx->img.bits_per_pixel / 8));
	// draw_map(mlx); // Draw Map in 2D
	player = mlx->player;
	// float time = 0;
	// float oldTime = 0;

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		float cameraX = 2 * x / (float)WIN_WIDTH - 1;
		float rayDirX = player->dir_x + player->plane_x * cameraX;
		float rayDirY = player->dir_y + player->plane_y * cameraX;

		int	mapX = (int)player->pos_x;
		int	mapY = (int)player->pos_y;

		float	sideDistX;
		float	sideDistY;

		double	deltaDistX = fabs(1 / rayDirX);
		double	deltaDistY = fabs(1 / rayDirY);
		double	perpWallDist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX > 13 || mapY > 10 || mapX < 0 || mapY < 0 || mlx->map[mapY][mapX] == '1')
			{
				hit = 1;
				// draw_square(mapX * BLOCK_SIZE, mapY * BLOCK_SIZE, BLOCK_SIZE, 0xFF0000, &mlx->img);
			}
		}

		// t_point start = {round(player->pos_x * BLOCK_SIZE), round(player->pos_y * BLOCK_SIZE)};
		// t_point end = {mapX * BLOCK_SIZE, mapY * BLOCK_SIZE};
		// draw_line(start, end, 0xFF0000, &mlx->img);

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int line_height = (int)(WIN_HEIGHT / perpWallDist);

		int	draw_start = -line_height / 2 + WIN_HEIGHT / 2;

		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;

		while (draw_start < draw_end)
		{
			put_pixel(x, draw_start, 255, &mlx->img);
			draw_start++;
		}
	}
	// draw_square(player->pos_x * BLOCK_SIZE, player->pos_y * BLOCK_SIZE, 32, 0xFFFF00, &mlx->img); // Draw Player in 2D
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
	// mlx_loop_hook(mlx.mlx, &draw_loop, &mlx);
	mlx_loop_hook(mlx.mlx, &new_draw_loop, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
