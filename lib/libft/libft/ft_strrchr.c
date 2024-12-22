/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:56:19 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 10:07:45 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	if (c > 255)
		c -= 256;
	pos = ft_strlen(s) + 1;
	if (c == '\0')
		return ((char *)(s + pos - 1));
	while (--pos != -1)
		if (s[pos] == c)
			return ((char *)(s + pos));
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	const char	*str = "Hello, World!";
	char		target = '!';
	printf("Found the last '%c' at position %ld.\n",
	 target, strrchr(str, target) - str);
	
	printf("\n");
	
	printf("ft_:\n");
	const char	*str1 = "Hello, World!";
	char		target1 = '!';
	printf("Found the last '%c' at position %ld.\n",
	 target1, ft_strrchr(str1, target1) - str1);
}
*/
