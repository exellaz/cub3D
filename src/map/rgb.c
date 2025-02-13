/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:35:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/13 11:49:44 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "map.h"

static char	**valid_rgb(t_list *raw, int *fc);

t_list	*get_rgb(t_list *raw, int (*rgb)[3])
{
	char	**split;
	int		fc;
	int		i;
	int		j;

	count_cfg(raw, 2, "RGB count is not 2");
	i = -1;
	while (++i < 2)
	{
		split = valid_rgb(raw, &fc);
		j = -1;
		while (++j < 3)
		{
			if (!is_num(split[j]))
				error_exit("non-numeric RGB value");
			rgb[fc][j] = ft_atoi(split[j]);
			if (rgb[fc][j] < 0 || rgb[fc][j] > 255)
				error_exit("Invalid RGB value");
		}
		raw = raw->next;
	}
	return (raw);
}

static char	**valid_rgb(t_list *raw, int *fc)
{
	char	**split;

	split = split_cfg(raw->content);
	if (count_arr(split) != 2)
		error_exit("RGB count is not 2");
	if (ft_strcmp(split[0], "F") == 0)
		*fc = 0;
	else if (ft_strcmp(split[0], "C") == 0)
		*fc = 1;
	else
		error_exit("Invalid RGB identifier");
	split = ft_split(split[1], ',');
	if (count_arr(split) != 3)
		error_exit("RGB value count is not 3");
	return (split);
}
