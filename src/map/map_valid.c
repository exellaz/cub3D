/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/01/16 14:27:55 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "map.h"

void	validate_map(t_list *map)
{
	// check texture path
	// check rgb
	// check identifier
	if (!valid_iden(map))
		error_exit("Invalid identifier in map");
	// check walls
	if (!valid_walls(map))
		error_exit("Invalid walls in map");
}

bool	valid_iden(t_list *map)
{
	char	*iden;
	char	*line;

	iden = " 01NSEW";
	while (map)
	{
		line = (char *)map->content;
		printf("line: [%s]\n", line);
		while (*line)
		{
			if (!ft_strchr(iden, *line))
				return (false);
			line++;
		}
		map = map->next;
	}
	return (true);
}

bool	valid_walls(t_list *map)
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
			return (false);
		while (map_arr[i][j] && !is_whitespace(map_arr[i][j]))
			j++;
		if (map_arr[i][j - 1] != '1')
			return (false);
	}
	i = -1;
	while (map_arr[0][++i])
	{
		j = -1;
		while (map_arr[++j] && is_whitespace(map_arr[j][i]))
			;
		if (map_arr[j][i] != '1')
			return (false);
		while (map_arr[j] && !is_whitespace(map_arr[j][i]))
			j++;
		if (map_arr[j - 1][i] != '1')
			return (false);
	}
	return true;
}
