/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:36:01 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 09:28:14 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;

	i = -1;
	while (++i < (int)n)
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	buffer[] = "Hello, World!";
	char	character = '\0';
	printf("Found character '%c' at position %ld.\n",
	 character, (char *)memchr(buffer, character, sizeof(buffer)) - buffer);
	 
	char	buffer1 = "012345";
	printf("Found character '%c' at position %ld.\n",
	 character, (char *)memchr(buffer1, 2 + 256, sizeof(buffer1)) - buffer1);
	
	
	printf("\n");
	
	printf("ft_:\n");
	char	buffer2[] = "Hello, World!";
	char	character1 = '\0';
	printf("Found character '%c' at position %ld.\n",
	 character1, (char *)ft_memchr(buffer2, character1,
	  sizeof(buffer2)) - buffer2);
	  
	char	buffer = "012345";
	printf("Found character '%c' at position %ld.\n",
	 character, (char *)memchr(buffer, 2 + 256, sizeof(buffer)) - buffer);
}
*/
