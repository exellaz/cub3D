# include "cub3D.h"

int	main(void)
{
	t_mlx m;
	t_img i;

	setup_mlx(&m);
	i.img = mlx_new_image(m.mlx, 800, 600);
	i.addr = mlx_get_data_addr(i.img, &i.bits_per_pixel, &i.line_length,
								&i.endian);
	my_mlx_pixel_put(&i, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(m.mlx, m.win, i.img, 0, 0);
	mlx_loop(m.mlx);
}
