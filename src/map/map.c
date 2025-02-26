/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazzite <bazzite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/02/26 21:22:52 by bazzite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

static t_map	*init_map(void);
static int		get_map_width(t_list *map);

t_map	*parse_map(int file, void *mlx)
{
	t_map	*map_data;
	t_list	*raw;
	t_list	*remain;

	map_data = init_map();
	raw = load_file(file);
	remain = get_texture_path(raw, map_data->texture, &map_data->texture_count);
	remain = get_rgb(remain, map_data->fc_rgb);
	get_map(remain, &map_data->map_list, &map_data->width, &map_data->height);
	get_spawn(map_data->map_list, map_data->spawn);
	get_doors(map_data->map_list, &map_data->doors, &map_data->door_count);
	valid_texture_path(map_data->texture);
	valid_iden(map_data->map_list);
	valid_walls(map_data->map_list, map_data->height, map_data->spawn);
	load_textures(map_data->texture, mlx);
	map_data->map = lst_to_arr(map_data->map_list);
	return (map_data);
}

static t_map	*init_map(void)
{
	t_map	*map_data;

	map_data = mem_alloc(sizeof(t_map));
	map_data->map_list = NULL;
	map_data->map = NULL;
	map_data->doors = NULL;
	map_data->texture_count = 0;
	map_data->door_count = 0;
	map_data->width = 0;
	map_data->height = 0;
	return (map_data);
}

void	get_map(t_list *raw, t_list **map, int *width, int *height)
{
	t_list	*tmp;
	char	*line;
	int		i;

	*map = skip_empty_lines(raw);
	*width = get_map_width(*map);
	*height = 0;
	tmp = *map;
	while (tmp)
	{
		if (ft_strlen(tmp->content) <= (size_t) * width)
		{
			line = mem_alloc(*width + 1);
			ft_strlcpy(line, (char *)tmp->content, *width + 1);
			line[*width] = '\0';
			i = ft_strlen(line);
			while (i < *width)
				line[i++] = ' ';
			tmp->content = line;
		}
		*height += 1;
		tmp = tmp->next;
	}
}

static int	get_map_width(t_list *map)
{
	t_list	*tmp;
	int		max;

	max = 0;
	tmp = map;
	while (tmp)
	{
		((char *)tmp->content)[ft_strlen(tmp->content) - 1] = '\0';
		if (ft_strlen(tmp->content) > (size_t)max)
			max = ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	return (max);
}
