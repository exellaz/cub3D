/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2024/12/27 15:59:03 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "map.h"

# define DEBUG printf

t_map	*parse_map(int file)
{
	t_map	*map;
	t_list	*raw;
	t_list	*remain;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	raw = load_file(file);
	remain = get_texture_path(raw, map->texture_path);
	remain = get_rgb(remain, map->ceiling_rgb);
	remain = get_rgb(remain, map->floor_rgb);
	get_map(remain, &map->map);
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

t_list	*get_texture_path(t_list *raw, char **texture_path)
{
	int	i;

	while (((char *)raw->content)[0] == '\n')
		raw = raw->next;
	i = -1;
	while (++i < 4)
	{
		texture_path[i] = ft_split(raw->content, ' ')[1];
		raw = raw->next;
	}
	return (raw->next);
}

t_list	*get_rgb(t_list *raw, int *rgb)
{
	char	**split;
	char	*line;
	int		i;

	while (((char *)raw->content)[0] == '\n')
		raw = raw->next;
	line = ft_substr(raw->content, 2, ft_strlen(raw->content) - 2);
	split = ft_split(line, ',');
	i = -1;
	while (++i < 3)
		rgb[i] = ft_atoi(split[i]);
	return (raw->next);
}

int	get_map(t_list *raw, t_list **map)
{
	*map = raw;
	return (0);
}
