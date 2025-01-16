/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:29:44 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/16 11:25:32 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <Libft.h>

#include "map.h"

void	print_map(t_list *map)
{
	while (map)
	{
		printf("%s\n", (char *)map->content);
		map = map->next;
	}
}
