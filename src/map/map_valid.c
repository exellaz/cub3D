/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/01/16 09:47:32 by tjun-yu          ###   ########.fr       */
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
	int i;
	int rows = 0;
	int cols = 0;

	map_arr = lst_to_arr(map);
	// Calculate the number of rows and columns
	while (map_arr[rows])
		rows++;
	cols = ft_strlen(map_arr[0]);

	// Check the first and last rows
	for (i = 0; i < cols; i++)
	{
		if (map_arr[0][i] != '1' || map_arr[rows - 1][i] != '1')
			return false;
	}

	// Check the first and last columns
	for (i = 0; i < rows; i++)
	{
		if (map_arr[i][0] != '1' || map_arr[i][cols - 1] != '1')
			return false;
	}

	return true;
}
