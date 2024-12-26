/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2024/12/26 21:44:16 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "map.h"

t_map	*parse_map(int file)
{
	t_map	*map;
	t_list	*raw;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	raw = load_file(file);
	get_map(raw, &map->map);
	get_texture_path(raw, map->texture_path);
	get_rgb(raw, map->ceiling_rgb);
	get_rgb(raw, map->floor_rgb);
	return (map);
}

// takes a file descriptor as argument and returns a 2D array of strings
t_list	*load_file(int file)
{
	t_list	*map;
	char	*line;

	map = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_lstadd_back(&map, ft_lstnew(line));
		line = get_next_line(file);
	}
	return (map);
}

int	get_texture_path(t_list *raw, char **texture_path)
{

	return (0);
}

int	get_rgb(t_list *raw, int *rgb)
{

	return (0);
}

int	get_map(t_list *raw, t_list **map)
{

	return (0);
}
