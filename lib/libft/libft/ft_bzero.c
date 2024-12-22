/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:03:30 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:35:17 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	buffer[10];
	bzero(buffer, sizeof(buffer));
	printf("%s\n", buffer);

	printf("\n");

	printf("ft_:\n");
	char	buffer1[10];
	bzero(buffer1, sizeof(buffer1));
	printf("%s\n", buffer1);
}
*/
