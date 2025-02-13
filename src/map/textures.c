/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:10:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/13 14:53:30 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>
#include <mlx.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

static void	get_path(t_list **raw, t_texture *texture, int count);

t_list	*get_texture_path(t_list *raw, t_texture *texture, int *count)
{
	t_list	*tmp;
	int		i;

	i = -1;
	while (++i < 7)
		texture[i].path = NULL;
	raw = skip_empty_lines(raw);
	*count = 0;
	tmp = raw;
	while (!is_whitespace(((char *)tmp->content)[0]))
	{
		*count += 1;
		tmp = tmp->next;
	}
	get_path(&raw, texture, *count);
	if (*count < 4 || *count > 7)
		error_exit("Invalid texture count");
	return (raw->next);
}

static void	get_path(t_list **raw, t_texture *texture, int count)
{
	char	**split;
	int		i;

	i = -1;
	while (++i < count)
	{
		split = split_cfg((*raw)->content);
		if (ft_strcmp(split[0], "NO") == 0)
			texture[0].path = split[1];
		else if (ft_strcmp(split[0], "SO") == 0)
			texture[1].path = split[1];
		else if (ft_strcmp(split[0], "WE") == 0)
			texture[2].path = split[1];
		else if (ft_strcmp(split[0], "EA") == 0)
			texture[3].path = split[1];
		else if (ft_strcmp(split[0], "FL") == 0)
			texture[4].path = split[1];
		else if (ft_strcmp(split[0], "CL") == 0)
			texture[5].path = split[1];
		else if (ft_strcmp(split[0], "DO") == 0)
			texture[6].path = split[1];
		else
			error_exit("Invalid texture identifier");
		*raw = (*raw)->next;
	}
	if ((texture[4].path && !texture[5].path)
		|| (!texture[4].path && texture[5].path))
		error_exit("Missing floor or ceiling texture");
	i = -1;
	while (++i < count)
		if (!texture[i].path)
			error_exit("Missing texture path");
}

void	load_textures(t_texture *texture, void *mlx, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
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
		mlx_destroy_image(mlx, texture[i].img->img);
		mem_free(texture[i].img);
	}
}
