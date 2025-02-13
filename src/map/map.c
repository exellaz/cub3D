/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/02/13 11:57:08 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

t_map	*parse_map(int file, void *mlx)
{
	t_map	*map;
	t_list	*raw;
	t_list	*remain;

	map = mem_alloc(sizeof(t_map));
	raw = load_file(file);
	remain = get_texture_path(raw, map->texture, &map->texture_count);
	remain = get_rgb(remain, map->fc_rgb);
	get_map(remain, &map->map, &map->width, &map->height);
	get_spawn(map->map, map->spawn);
	get_doors(map->map, &map->door, &map->door_count);
	valid_texture_path(map->texture);
	valid_iden(map->map);
	valid_walls(map->map, map->height);
	load_textures(map->texture, mlx, map->texture_count);
	return (map);
}

void	get_map(t_list *raw, t_list **map, int *width, int *height)
{
	t_list	*tmp;
	char	*line;
	int		max;
	int		i;

	*map = skip_empty_lines(raw);
	max = 0;
	tmp = *map;
	while (tmp)
	{
		((char *)tmp->content)[ft_strlen(tmp->content) - 1] = '\0';
		if (ft_strlen(tmp->content) > (size_t)max)
			max = ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	*width = max;
	*height = 0;
	tmp = *map;
	while (tmp)
	{
		if (ft_strlen(tmp->content) <= (size_t)max)
		{
			line = mem_alloc(max + 1);
			ft_strlcpy(line, (char *)tmp->content, max + 1);
			line[max] = '\0';
			i = ft_strlen(line);
			while (i < max)
				line[i++] = ' ';
			tmp->content = line;
		}
		*height += 1;
		tmp = tmp->next;
	}
}

void	get_spawn(t_list *map, int *spawn)
{
	char	*line;
	int		i;
	int		j;

	map = skip_empty_lines(map);
	i = -1;
	while (map)
	{
		i += 1;
		line = map->content;
		j = -1;
		while (line[++j])
		{
			if (ft_strchr(SPAWN_IDEN, line[j]))
			{
				spawn[0] = i;
				spawn[1] = j;
				spawn[2] = line[j];
				return ;
			}
		}
		map = map->next;
	}
	if (!ft_strchr(SPAWN_IDEN, spawn[2]))
		error_exit("Invalid spawn point");
}
