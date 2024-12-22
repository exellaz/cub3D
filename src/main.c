# include "Libft.h"
# include "mlx.h"

int main(void)
{
	ft_printf("Hello, World!\n");
	ft_printf("%d\n", ft_isalpha('a'));

	void *mlx;
	void *win;
	(void)win;
	
	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "Hello, World!");
	mlx_loop(mlx);

	return (0);
}
