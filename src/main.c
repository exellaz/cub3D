#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"
#include <time.h>

#include <math.h>

void	raycast(t_vars *mlx);
void draw_line(t_point start, t_point end, int color, t_img *img);

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
	// printf("%d\n", DEBUG);
	raycast(mlx);
	float	speed = mlx->fps->frame_time * 2.5;
	float	rot_speed = mlx->fps->frame_time * 2.5;
	if (mlx->keys[KEY_W] == true)
	{
		player->pos_x += player->dir_x * speed;
		player->pos_y += player->dir_y * speed;
	}
	if (mlx->keys[KEY_S] == true)
	{
		player->pos_x -= player->dir_x * speed;
		player->pos_y -= player->dir_y * speed;
	}
	if (mlx->keys[KEY_A] == true)
	{
		player->pos_x -= player->plane_x * speed;
		player->pos_y -= player->plane_y * speed;
	}
	if (mlx->keys[KEY_D] == true)
	{
		player->pos_x += player->plane_x * speed;
		player->pos_y += player->plane_y * speed;

	}
	if (mlx->keys[0] == true)
	{
		float	old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);
		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);
	}
	if (mlx->keys[1] == true)
	{
		float	old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
		float	old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
	}
	if (DEBUG == 1)
	{
		t_point start = {round(player->pos_x * BLOCK_SIZE) + 8, round(player->pos_y * BLOCK_SIZE) + 8};
		t_point end = {round(player->pos_x * BLOCK_SIZE + (player->dir_x * 32)), round(player->pos_y * BLOCK_SIZE + (player->dir_y * 32))};
		draw_line(start, end, 0xFF0000, &mlx->img);
		draw_map(mlx); // Draw Map in 2D
		draw_square(player->pos_x * BLOCK_SIZE, player->pos_y * BLOCK_SIZE, 16, 0xFFFF00, &mlx->img); // Draw Player in 2D
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac, (void)av;
	t_vars		vars;

	init_vars(&vars);
	mlx_loop_hook(vars.mlx, &draw_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
