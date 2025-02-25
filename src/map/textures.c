/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:10:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/25 16:01:32 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>
#include <mlx.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

void	load_textures(t_texture *texture, void *mlx)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (!texture[i].path)
			continue ;
		texture[i].img = mem_alloc(sizeof(t_img));
		texture[i].img->img = mlx_xpm_file_to_image(mlx, texture[i].path,
				&texture[i].width, &texture[i].height);
		if (!texture[i].img->img)
			error_exit("Invalid texture");
		texture[i].img->addr = (int *)mlx_get_data_addr(texture[i].img->img,
				&texture[i].img->bits_per_pixel, &texture[i].img->line_length,
				&texture[i].img->endian);
	}
}

void	free_texture(t_texture *texture, void *mlx)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (!texture[i].path)
			continue ;
		mlx_destroy_image(mlx, texture[i].img->img);
		mem_free(texture[i].img);
	}
}
