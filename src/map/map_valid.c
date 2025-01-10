/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/01/10 09:44:52 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
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
	(void)map;
	return (true);
}
