/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:37:15 by we                #+#    #+#             */
/*   Updated: 2025/01/07 10:38:14 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "map.h"

void	validate_map(t_list *map)
{
	// check texture path
	// check rgb
	// check identifier
	if (!valid_iden(map))
		error("Invalid identifier in map");
	// check walls
	return (0);
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
	return (true);
}
