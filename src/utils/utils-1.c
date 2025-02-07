#include <Libft.h>
#include <mlx.h>

#include "graphics.h"
#include "map.h"
#include "utils.h"

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_img(t_img *img, void *mlx)
{
	mlx_destroy_image(mlx, img->img);
	mem_free(img);
}
