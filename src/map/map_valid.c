/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/02/06 18:15:46 by kkhai-ki         ###   ########.fr       */
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
	char	*iden;
	char	*line;
	int		spawn;
	t_list	*tmp;

	iden = " 01NSEW";
	tmp = map;
	while (tmp)
	{
		line = (char *)tmp->content;
		while (*line)
		{
			if (!ft_strchr(iden, *line))
				error_exit("Invalid identifier");
			line++;
		}
		tmp = tmp->next;
	}
	spawn = 0;
	tmp = map;
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
