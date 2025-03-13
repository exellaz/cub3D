/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:29:44 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/03/13 14:11:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <c_libft.h>

#include "map.h"

void	print_texture_path(t_texture *texture)
{
	int	i;

	i = -1;
	while (++i < 4)
		printf("%s\n", texture[i].path);
	printf("\n");
}

void	print_rgb(int (*rgb)[3])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 3)
			printf("%d ", rgb[i][j]);
		printf("\n");
	}
	printf("\n");
}

void	print_spawn(int *spawn)
{
	int	i;

	i = -1;
	while (++i < 3)
		printf("%d ", spawn[i]);
	printf("\n\n");
}

void	print_map(t_list *map)
{
	while (map)
	{
		printf("%s\n", (char *)map->content);
		map = map->next;
	}
	printf("\n");
}
