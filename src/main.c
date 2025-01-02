#include "libmem.h"
#include "graphics.h"
#include "events.h"
#include "enum.h"
#include "cub3D.h"

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
}

int	main(int ac, char **av)
{
	(void)ac, (void)av;
	t_mlx	mlx;

	setup_mlx(&mlx);
	draw_square(WIN_WIDTH / 2, WIN_HEIGHT / 2, 40, 0xFFFF00, &mlx.img);
	mlx_loop(mlx.mlx);
}
