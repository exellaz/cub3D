/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:11:34 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/24 13:39:05 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	int			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	i = -1;
	while (++i < (int)n)
		dest_ptr[i] = src_ptr[i];
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	source[] = "Hello, World!";
	char	destination[20];
	memcpy(destination, source, 13);
	destination[13] = 0;
	printf("Copied string: %s\n", destination);

	memcpy(NULL, source, 20);

	printf("\n");
	
	printf("ft_:\n");
	char	source1[] = "Hello, World!";
	char	destination1[20];
	ft_memcpy(destination1, source1, 13);
	destination1[13] = 0;
	printf("Copied string: %s\n", destination1);

	ft_memcpy(NULL, source1, 20);
}
*/
