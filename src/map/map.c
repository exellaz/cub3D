/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/02/26 08:03:29 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

static void	init_map(t_map *map_data);
static int	get_map_width(t_list *map);

t_map	*parse_map(int file, void *mlx)
{
	t_map	*map_data;
	t_list	*raw;
	t_list	*remain;

	map_data = mem_alloc(sizeof(t_map));
	init_map(map_data);
	raw = load_file(file);
	remain = get_texture_path(raw, map_data->texture_data, &map_data->texture_count);
	remain = get_rgb(remain, &map_data->floor_color, &map_data->ceiling_color);
	get_map(remain, &map_data->map_list, &map_data->width, &map_data->height);
	get_spawn(map_data->map_list, map_data->spawn);
	get_doors(map_data->map_list, &map_data->doors, &map_data->door_count);
	valid_texture_path(map_data->texture_data);
	valid_iden(map_data->map_list);
	valid_walls(map_data->map_list, map_data->height);
	load_textures(map_data->texture_data, mlx);
	valid_textures(map_data->texture_data);
	map_data->map = lst_to_arr(map_data->map_list);
	map_data->tex_width = map_data->texture_data->width;
	map_data->tex_height = map_data->texture_data->height;
	return (map_data);
}

static void	init_map(t_map *map_data)
{
	map_data->map_list = NULL;
	map_data->map = NULL;
	map_data->doors = NULL;
	map_data->texture_count = 0;
	map_data->door_count = 0;
	map_data->width = 0;
	map_data->height = 0;
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
