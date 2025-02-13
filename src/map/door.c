/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:53:00 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/13 11:57:25 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "map.h"

static int	count_doors(t_list *map);

void	get_doors(t_list *map, t_door **door, int *count)
{
	t_list	*tmp;
	int		i;
	int		j;
	int		k;

	*count = count_doors(map);
	*door = mem_alloc(sizeof(t_door) * *count);
	tmp = map;
	i = 0;
	k = -1;
	while (tmp)
	{
		j = -1;
		while (((char *)tmp->content)[++j])
		{
			if (((char *)tmp->content)[j] == 'D')
			{
				(*door)[++k].x = j;
				(*door)[k].y = i;
				(*door)[k].is_open = false;
			}
		}
		i++;
		tmp = tmp->next;
	}
}

static int	count_doors(t_list *map)
{
	t_list	*tmp;
	int		i;

	tmp = map;
	i = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->content, 'D'))
			i++;
		tmp = tmp->next;
	}
	return (i);
}
