/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:01:31 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/02/29 18:14:48 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*c_strjoin(char **str1, const char *str2)
{
	char	*new_str;
	int		total_size;

	if (*str1 == NULL)
	{
		*str1 = (char *)malloc(1);
		if (*str1 == NULL)
			return (NULL);
	}
	total_size = ft_strlen(*str1) + ft_strlen(str2);
	new_str = (char *)malloc(total_size + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, *str1, ft_strlen(*str1));
	ft_memmove(new_str + ft_strlen(*str1), str2, ft_strlen(str2) + 1);
	free(*str1);
	return (new_str);
}
