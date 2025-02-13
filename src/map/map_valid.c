/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/02/13 13:54:54 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "map.h"

static void	valid_spawn(t_list *map);
static void	check_y_walls(char **map_arr, int height);

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
	valid_spawn(map);
}

static void	valid_spawn(t_list *map)
{
	int		spawn_count;
	t_list	*tmp;
	int		i;

	spawn_count = 0;
	tmp = map;
	while (tmp)
	{
		i = -1;
		while (((char *)tmp->content)[++i])
		{
			if (ft_strchr(SPAWN_IDEN, ((char *)tmp->content)[i]))
			{
				spawn_count += 1;
				((char *)tmp->content)[i] = '0';
			}
		}
		tmp = tmp->next;
	}
	if (spawn_count != 1)
		error_exit("Invalid spawn point");
}

void	valid_walls(t_list *map, int height)
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
	check_y_walls(map_arr, height);
}

static void	check_y_walls(char **map_arr, int height)
{
	int	empty;
	int	i;
	int	j;

	i = -1;
	while (map_arr[0][++i])
	{
		empty = 0;
		j = 0;
		while (j < height && is_whitespace(map_arr[j++][i]))
			++empty;
		if (empty == height)
			continue ;
		if (map_arr[j - 1][i] != '1')
			error_exit("Invalid wall !");
		while (map_arr[j] && !is_whitespace(map_arr[j][i]))
			j++;
		if (map_arr[j - 1][i] != '1')
			error_exit("Invalid wall");
	}
}
