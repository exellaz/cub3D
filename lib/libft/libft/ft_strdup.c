/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:28:06 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/23 15:28:26 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*duplicate;
	int		i;

	duplicate = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != 0)
		duplicate[i] = str[i];
	duplicate[i] = 0;
	return (duplicate);
}

/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	const char	*original = "Hello, World!";
	char		*duplicate = strdup(original);
	printf("%s\n", duplicate);

	printf("\n");

	printf("ft_:\n");
	const char	*original1 = "Hello, World!";
	char		*duplicate1 = ft_strdup(original1);
	printf("%s\n", duplicate1);
}
*/
