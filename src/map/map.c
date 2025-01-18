/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/01/16 14:58:43 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "map.h"

t_map	*parse_map(int file)
{
	t_map	*map;
	t_list	*raw;
	t_list	*remain;

	map = mem_alloc(sizeof(t_map));
	raw = load_file(file);
	remain = get_texture_path(raw, map->texture_path);
	remain = get_rgb(remain, map->fc_rgb);
	get_map(remain, &map->map);
	get_spawn(map->map, map->spawn);
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

// TODO: check if there are exactly 4 texture paths
t_list	*get_texture_path(t_list *raw, char **texture_path)
{
	char	**split;
	int		i;

	raw = skip_empty_lines(raw);
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
			error_exit("Invalid texture identifier");
		raw = raw->next;
	}
	i = -1;
	while (++i < 4)
		if (!texture_path[i])
			error_exit("Missing texture path");
	return (raw->next);
}

// TODO: check if there are exactly 2 RGB values
t_list	*get_rgb(t_list *raw, int (*rgb)[3])
{
	char	**split;
	int		fc;
	int		i;
	int		j;

	raw = skip_empty_lines(raw);
	i = -1;
	while (++i < 2)
	{
		split = ft_split((char *)raw->content, '\n');
		split = ft_split(split[0], ' ');
		if (ft_strcmp(split[0], "F") == 0)
			fc = 0;
		else if (ft_strcmp(split[0], "C") == 0)
			fc = 1;
		else
			error_exit("Invalid RGB identifier");
		split = ft_split(split[1], ',');
		j = -1;
		while (++j < 3)
		{
			if (!is_num(split[j]))
				error_exit("non-numeric RGB value");
			rgb[fc][j] = ft_atoi(split[j]);
			if (rgb[fc][j] < 0 || rgb[fc][j] > 255)
				error_exit("Invalid RGB value");
		}
		raw = raw->next;
	}
	return (raw);
}

void	get_map(t_list *raw, t_list **map)
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
	i = -1;
	tmp = *map;
	while (tmp)
	{
		if (ft_strlen(tmp->content) < (size_t)max)
		{
			line = mem_alloc(max + 1);
			ft_strlcpy(line, (char *)tmp->content, max + 1);
			i = ft_strlen(line);
			while (i < max)
				line[i++] = ' ';
			line[max] = '\0';
			tmp->content = line;
		}
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
			if (line[j] == 'N' || line[j] == 'S'
				|| line[j] == 'E' || line[j] == 'W')
			{
				spawn[0] = i;
				spawn[1] = j;
				spawn[2] = line[j];
				return ;
			}
		}
		map = map->next;
	}
}
