/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazzite <bazzite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/02/26 21:20:03 by bazzite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "map.h"

static void	valid_spawn(t_list *map);
static void	flood_fill(int x, int y, char **map_arr, int height);

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

void	valid_walls(t_list *map, int height, int *spawn)
{
	char	**map_arr;

	map_arr = lst_to_arr(map);
	flood_fill(spawn[0], spawn[1], map_arr, height);
}

static void	flood_fill(int y, int x, char **map_arr, int height)
{
	if (x < 0 || x > (int)ft_strlen(map_arr[0]) || y < 0 || y >= height)
		return ;
	if (map_arr[y][x] == ' ')
		error_exit("Invalid space");
	if (map_arr[y][x] == '1' || map_arr[y][x] == 'D' || map_arr[y][x] == 'x')
		return ;
	map_arr[y][x] = 'x';
	flood_fill(y + 1, x, map_arr, height);
	flood_fill(y - 1, x, map_arr, height);
	flood_fill(y, x + 1, map_arr, height);
	flood_fill(y, x - 1, map_arr, height);
}
