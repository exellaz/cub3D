/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:03:51 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 12:26:29 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len || len == 0)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (substr == NULL || start >= s_len)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	// char const	*s = "1234567890";
	// printf("test 1: %s\n", ft_substr(s, 0, 3));
	// printf("test 2: %s\n", ft_substr(s, ft_strlen(s), 3));
	// printf("test 3: %s\n", ft_substr(s, 5, 5));
	// printf("test 4: %s\n", ft_substr(s, 5, 10));
	// printf("test 5: %s\n", ft_substr(s, ft_strlen(s) + 1, 3));

	char const *s1 = "tripouille";
}
*/
