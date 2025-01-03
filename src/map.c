/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/01/03 14:11:59 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "map.h"

t_map	*parse_map(int file)
{
	t_map	*map;
	t_list	*raw;
	t_list	*remain;

	map = mem_alloc(sizeof(t_map));
	if (!map)
		return (NULL);
	raw = load_file(file);
	remain = get_texture_path(raw, map->texture_path);
	remain = get_rgb(remain, map->cf_rgb);
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
	char	**split;
	int		i;

	while (((char *)raw->content)[0] == '\n')
		raw = raw->next;
	i = -1;
	while (++i < 4)
	{
		split = ft_split(raw->content, ' ');
		if (ft_strcmp(split[0], "NO") == 0)
			texture_path[0] = split[1];
		else if (ft_strcmp(split[0], "SO") == 0)
			texture_path[1] = split[1];
		else if (ft_strcmp(split[0], "WE") == 0)
			texture_path[2] = split[1];
		else if (ft_strcmp(split[0], "EA") == 0)
			texture_path[3] = split[1];
		else
			error_exit("Invalid texture path");
		raw = raw->next;
	}
	i = -1;
	while (++i < 4)
		if (!texture_path[i])
			error_exit("Missing texture path");
	return (raw->next);
}

t_list	*get_rgb(t_list *raw, int (*rgb)[3])
{
	char	**split;
	char	*line;
	int		i;
	int		j;

	while (((char *)raw->content)[0] == '\n')
		raw = raw->next;
	i = -1;
	while (++i < 2)
	{
		line = ft_substr(raw->content, 2, ft_strlen(raw->content) - 2);
		split = ft_split(line, ',');
		j = -1;
		while (++j < 3)
			rgb[i][j] = ft_atoi(split[j]);
		raw = raw->next;
	}
	return (raw);
}

int	get_map(t_list *raw, t_list **map)
{
	*map = raw;
	return (0);
}
