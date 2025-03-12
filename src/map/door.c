/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:53:00 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/03/12 08:43:22 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "map.h"

static int	count_doors(t_list *map);
static void	init_doors_in_row(t_door *doors, t_list *tmp, int y, int *i);

void	get_doors(t_list *map, t_door **doors, int *count)
{
	t_list	*tmp;
	int		y;
	int		i;

	*count = count_doors(map);
	*doors = mem_alloc(sizeof(t_door) * *count);
	tmp = map;
	y = 0;
	i = 0;
	while (tmp)
	{
		init_doors_in_row(*doors, tmp, y, &i);
		y++;
		tmp = tmp->next;
	}
}

static int	count_doors(t_list *map)
{
	t_list	*tmp;
	char	*str;
	int		i;
	int		j;

	tmp = map;
	i = 0;
	while (tmp)
	{
		j = 0;
		str = tmp->content;
		while (str[j])
		{
			if (str[j] == 'D')
				i++;
			j++;
		}
		tmp = tmp->next;
	}
	return (i);
}

static void	init_doors_in_row(t_door *doors, t_list *tmp, int y, int *i)
{
	int	x;

	x = -1;
	while (((char *)tmp->content)[++x])
	{
		if (((char *)tmp->content)[x] == 'D')
		{
			doors[*i].x = x;
			doors[*i].y = y;
			doors[*i].is_open = false;
			doors[*i].progress = 0;
			(*i)++;
		}
	}
}

void	update_doors(t_map *map_data)
{
	t_door	*door;
	int		i;

	i = 0;
	while (i < map_data->door_count)
	{
		door = &map_data->doors[i];
		if (door->is_open && door->progress < 1.0)
		{
			door->progress += 0.05;
			if (door->progress > 1.0)
				door->progress = 1.0;
		}
		else if (!door->is_open && door->progress > 0.0)
		{
			door->progress -= 0.05;
			if (door->progress < 0.0)
				door->progress = 0.0;
		}
		if (door->is_open == true && door->progress == 1.0)
			map_data->map[door->y][door->x] = '0';
		else if (door->is_open == false)
			map_data->map[door->y][door->x] = 'D';
		i++;
	}
}

t_door	*find_door(t_map *map_data, int x, int y)
{
	int		i;
	t_door	*doors;
	t_door	*door;

	i = 0;
	doors = map_data->doors;
	while (i < map_data->door_count)
	{
		if (doors[i].x == x && doors[i].y == y)
		{
			door = &doors[i];
			return (door);
		}
		i++;
	}
	return (NULL);
}
