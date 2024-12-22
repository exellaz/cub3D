/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:34:41 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:37:20 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)s;
	i = -1;
	while (++i < (int)n)
		ptr[i] = c;
	return (s);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	buffer[10];
	int		value = 42;
	memset(buffer, value, sizeof(buffer));
	for (int i = 0; (size_t)i < sizeof(buffer); i++)
		printf("buffer[%d] = %c\n", i, (int)buffer[i]);

	printf("\n");

	printf("ft_:\n");
	char	buffer1[10];
	int		value1 = 42;
	memset(buffer1, value1, sizeof(buffer1));
	for (int i = 0; (size_t)i < sizeof(buffer1); i++)
		printf("buffer1[%d] = %c\n", i, (int)buffer1[i]);
}
*/
