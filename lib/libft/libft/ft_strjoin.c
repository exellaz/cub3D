/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:33:59 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/02 14:54:37 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	total_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)mem_alloc(total_size * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_memmove(new_str, s1, ft_strlen(s1));
	ft_memmove(new_str + ft_strlen(s1), s2, ft_strlen(s2));
	new_str[total_size - 1] = 0;
	return (new_str);
}

/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char const	s1[] = "12345";
	char const	s2[] = "67890";
	printf("test 1: %s\n", ft_strjoin(s1, s2));
	printf("test 2: %s\n", ft_strjoin(s2, s1));
}
*/
