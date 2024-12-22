/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:37:48 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:38:14 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		i;

	if (size > 0)
	{
		i = -1;
		while (src[++i] != 0 && (size_t)i < size - 1)
			dest[i] = src[i];
		dest[i] = 0;
	}
	return (ft_strlen(src));
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("size is sizeof dest:\n");
	char		dest[10];
	const char	src[] = "Hello World!!!";
	size_t		copied = strlcpy(dest, src, 100);
	printf("Copied: %zu characters\n", copied);
	printf("Destination: %s\n", dest);

	printf("\n");
	
	printf("size is sizeof src:\n");
	char		dest1[10];
	const char	src1[] = "Hello World!!!";
	size_t		copied1 = strlcpy(dest1, src1, sizeof(dest));
	printf("Copied: %zu characters\n", copied1);
	printf("Destination: %s\n", dest1);
}
*/
