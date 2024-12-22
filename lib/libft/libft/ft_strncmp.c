/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:11:49 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/23 15:11:17 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != 0 && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	s1[] = "abcde";
	char	s2[] = "abcdefg";

	printf("original:\n");
	printf("%s, %s, 3: %d\n", s1, s2, strncmp(s1, s2, 3));
	printf("%s, %s, 5: %d\n", s1, s2, strncmp(s1, s2, 5));
	printf("%s, %s, 6: %d\n", s1, s2, strncmp(s1, s2, 6));
	printf("%s, %s, 6: %d\n", s2, s1, strncmp(s2, s1, 6));
	printf("%s, %s, 10: %d\n", s1, s2, strncmp(s1, s2, 10));
	printf("%s, %s, 10: %d\n", s2, s1, strncmp(s2, s1, 10));
	printf("\n");
	printf("ft_:\n");
	printf("%s, %s, 3: %d\n", s1, s2, ft_strncmp(s1, s2, 3));
	printf("%s, %s, 5: %d\n", s1, s2, ft_strncmp(s1, s2, 5));
	printf("%s, %s, 6: %d\n", s1, s2, ft_strncmp(s1, s2, 6));
	printf("%s, %s, 6: %d\n", s2, s1, ft_strncmp(s2, s1, 6));
	printf("%s, %s, 10: %d\n", s1, s2, ft_strncmp(s1, s2, 10));
	printf("%s, %s, 10: %d\n", s2, s1, ft_strncmp(s2, s1, 10));
}
*/
