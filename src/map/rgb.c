/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:35:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/25 11:05:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "map.h"

static char	**valid_rgb(t_list *raw, int *fc);
static int	rgb_to_int(int r, int g, int b);

t_list	*get_rgb(t_list *raw, int *floor_color, int *ceiling_color)
{
	char	**split;
	int		fc;
	int		i;
	int		j;
	int		rgb[2][3];

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
	*floor_color = rgb_to_int(rgb[0][0], rgb[0][1], rgb[0][2]);
	*ceiling_color = rgb_to_int(rgb[1][0], rgb[1][1], rgb[1][2]);
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

static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}