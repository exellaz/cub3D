/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:01:31 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/02 15:06:47 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char **str1, const char *str2)
{
	char	*new_str;
	int		total_size;

	if (*str1 == NULL)
	{
		*str1 = (char *)mem_alloc(1);
		if (*str1 == NULL)
			return (NULL);
	}
	total_size = ft_strlen(*str1) + ft_strlen(str2);
	new_str = (char *)mem_alloc(total_size + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, *str1, ft_strlen(*str1));
	ft_memmove(new_str + ft_strlen(*str1), str2, ft_strlen(str2) + 1);
	mem_free(*str1);
	return (new_str);
}

char	*ft_memmove(char *dest, const char *src, int src_len)
{
	int	i;

	i = -1;
	if (src < dest)
		while (--src_len >= 0)
			dest[src_len] = src[src_len];
	else
		while (++i < src_len)
			dest[i] = src[i];
	return (dest);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0)
		++len;
	return (len);
}
