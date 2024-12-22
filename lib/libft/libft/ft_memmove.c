/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:30:55 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/24 13:35:22 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_ptr = dest;
	src_ptr = src;
	i = n + 1;
	if (src_ptr < dest_ptr && src_ptr + n > dest_ptr)
		while (--i > 0)
			dest_ptr[i - 1] = src_ptr[i - 1];
	else
	{
		i = -1;
		while (++i < n)
			dest_ptr[i] = src_ptr[i];
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	str[] = "1234567890";
	memmove(str + 0, str + 5, 5);
	printf("str : %s\n",str);
	
	char	str1[] = "1234567890";
	memmove(str1 + 5, str1 + 0, 5);
	printf("str1: %s\n", str1);

	printf("\n");

	printf("ft_:\n");
	char	str2[] = "1234567890";
	memmove(str2 + 0, str2 + 5, 5);
	printf("str2: %s\n",str2);
	
	char	str3[] = "1234567890";
	memmove(str3 + 5, str3 + 0, 5);
	printf("str3: %s\n", str3);

	char	*src = "the cake is a lie !\0I'm hidden lol\r\n";
	char	buff[0xF0];
	ft_memmove(buff, src, 100);
	printf("%s\n", buff);
}
*/
