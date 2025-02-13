/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/02/13 13:34:48 by kkhai-ki         ###   ########.fr       */
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
	int		spawn;
	t_list	*tmp;

	spawn = 0;
	tmp = map;
	while (tmp)
	{
		if (ft_strchr(tmp->content, 'N') || ft_strchr(tmp->content, 'S')
			|| ft_strchr(tmp->content, 'E') || ft_strchr(tmp->content, 'W'))
			spawn++;
		tmp = tmp->next;
	}
	if (spawn != 1)
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
