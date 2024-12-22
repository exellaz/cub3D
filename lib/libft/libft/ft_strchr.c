/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:43:55 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 10:01:29 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (c > 255)
		c -= 256;
	i = -1;
	while (s[++i] != 0)
		if (s[i] == c)
			return ((char *)s + i);
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	const char	*str = "Hello, World!";
	char		target = '\0';
	printf("Found '%c' at position %ld.\n", target, strchr(str, target) - str);

	printf("\n");

	printf("ft_:\n");
	const char	*str1 = "Hello, World!";
	char		target1 = '\0';
	printf("Found '%c' at position %ld.\n", target1,
	 ft_strchr(str1, target1) - str1);
}
*/
