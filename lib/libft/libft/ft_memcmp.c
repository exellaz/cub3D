/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:52:18 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 15:29:39 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] - ptr2[i] != 0)
			return (ptr1[i] - ptr2[i]);
		++i;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	str1[] = "apple";
	char	str2[] = "apples";
	printf("str1 - str2: %d\n", memcmp(str1, str2, 3));

	printf("\n");

	printf("ft_:\n");
	char	str3[] = "apple";
	char	str4[] = "apples";
	printf("str3 - str4: %d\n", ft_memcmp(str3, str4, 3));
}
*/
