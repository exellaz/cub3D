/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/02/06 12:21:09 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "map.h"

void	validate_map(t_map *map)
{
	valid_texture_path(map->texture);
	valid_iden(map->map);
	valid_walls(map->map);
}

void	valid_texture_path(t_texture *texture)
{
	char	*path;
	int		fd;
	int		i;

	i = -1;
	while (++i < 4)
	{
		path = texture[i].path;
		if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
			error_exit("Invalid texture extension");
		fd = open(path, O_RDONLY);
		if (fd < 0)
			error_exit(strerror(errno));
		close(fd);
	}
}

void	valid_iden(t_list *map)
{
	char	*line;
	int		spawn;
	t_list	*tmp;

	tmp = map;
	while (tmp)
	{
		line = (char *)tmp->content;
		while (*line)
		{
			if (!ft_strchr(VALID_IDEN, *line))
				error_exit("Invalid identifier");
			line++;
		}
		tmp = tmp->next;
	}
	spawn = 0;
	tmp = map;
	while (tmp)
	{
		// DEBUG("content: %s\n", (char *)tmp->content);
		if (ft_strchr(tmp->content, 'N') || ft_strchr(tmp->content, 'S')
			|| ft_strchr(tmp->content, 'E') || ft_strchr(tmp->content, 'W'))
			spawn++;
		tmp = tmp->next;
	}
	if (spawn != 1)
		error_exit("Invalid spawn point");
}

void	valid_walls(t_list *map)
{
	char	**map_arr;
	int		i;
	int		j;

	map_arr = lst_to_arr(map);
	i = -1;
	while (map_arr[++i])
	{
		j = -1;
		while (map_arr[i][++j] && is_whitespace(map_arr[i][j]))
			;
		if (map_arr[i][j] != '1')
			error_exit("Invalid wall");
		while (map_arr[i][j] && !is_whitespace(map_arr[i][j]))
			j++;
		if (map_arr[i][j - 1] != '1')
			error_exit("Invalid wall");
	}
	i = -1;
	while (map_arr[0][++i])
	{
		j = -1;
		while (map_arr[++j] && is_whitespace(map_arr[j][i]))
			;
		if (map_arr[j][i] != '1')
			error_exit("Invalid wall");
		while (map_arr[j] && !is_whitespace(map_arr[j][i]))
			j++;
		if (map_arr[j - 1][i] != '1')
			error_exit("Invalid wall");
	}
}
