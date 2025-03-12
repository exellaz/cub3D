/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:10:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/03/12 13:22:45 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>
#include <mlx.h>

#include "error.h"
#include "utils.h"
#include "map.h"

void	load_textures(t_texture *texture, void *mlx, int count)
{
	int	i;

	i = -1;
	while (++i < count)
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

void	free_texture(t_texture *texture, void *mlx, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (!texture[i].path)
			continue ;
		mlx_destroy_image(mlx, texture[i].img->img);
		mem_free(texture[i].img);
	}
}

void	valid_textures(t_texture *texture_data)
{
	int	i;
	int	temp;

	i = 0;
	temp = texture_data[i].width;
	while (++i < 7)
	{
		if (!texture_data[i].path)
			continue ;
		if (texture_data[i].width != temp)
			error_exit("Texture widths not the same");
	}
	i = 0;
	temp = texture_data[i].height;
	while (++i < 7)
	{
		if (!texture_data[i].path)
			continue ;
		if (texture_data[i].height != temp)
			error_exit("Texture heights not the same");
	}
}

void	init_texture_pixel_data(t_map *map_data, int tex_width, int x, int y)
{
	int	i;
	int	j;
	int	tex_i;

	i = -1;
	j = -1;
	while (++i < 7)
	{
		if (!map_data->texture_data[i].path)
			continue ;
		tex_i = y * tex_width + x;
		map_data->texture[++j][tex_i] = \
			(int)(map_data->texture_data[i].img->addr[tex_i]);
	}
}

void	init_textures(t_map *map_data)
{
	int	x;
	int	y;
	int	tex_width;
	int	tex_height;

	tex_width = map_data->tex_width;
	tex_height = map_data->tex_height;
	map_data->texture = mem_alloc(sizeof(int *) * map_data->texture_count);
	x = -1;
	while (++x < map_data->texture_count)
		map_data->texture[x] = mem_alloc(sizeof(int) * tex_height * tex_width);
	y = -1;
	while (++y < tex_height)
	{
		x = -1;
		while (++x < tex_width)
			init_texture_pixel_data(map_data, tex_width, x, y);
	}
}
