/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/02/13 13:35:08 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

static int	get_map_width(t_list *map);

t_map	*parse_map(int file, void *mlx)
{
	t_map	*map_data;
	t_list	*raw;
	t_list	*remain;

	map_data = mem_alloc(sizeof(t_map));
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
