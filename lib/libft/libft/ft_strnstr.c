/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:45:20 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/27 09:23:18 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	size_t	j;

	if ((haystack == NULL || needle == NULL) && len == 0)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (ft_strlen(haystack) < needle_len)
		return (NULL);
	i = 0;
	while (i <= len - needle_len)
	{
		j = 0;
		while (j < needle_len && haystack[i + j] == needle[j])
			++j;
		if (j == needle_len)
			return ((char *)(haystack + i));
		++i;
	}
	return (NULL);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	const char	*haystack = "This is a test string for strnstr function.";
	const char	*needle = "";
	size_t		len = 0;
	printf("Found '%s' at position %ld.\n",
	 needle, strnstr(haystack, needle, len) - haystack);
	
	printf("\n");

	printf("ft_:\n");
	const char	*haystack1 = "This is a test string for strnstr function.";
	const char	*needle1 = "";
	size_t		len1 = 0;
	printf("Found '%s' at position %ld.\n",
	 needle1, ft_strnstr(haystack1, needle1, len1) - haystack1);

	printf("\n");
	
	printf("Libft-unit-test:\n");
	char	*s1 = "MZIRIBMZIRIBMZE123";
	char	*s2 = "MZIRIBMZE";
	size_t	max = strlen(s2);
	
	char	*i1 = strnstr(s1, NULL, max);
	printf("Found '%s' at position %ld.\n",
	 s2, i1 - s1);
	 
	char	*i2 = ft_strnstr(s1, NULL, max);
	printf("Found '%s' at position %ld.\n",
	 s2, i2 - s1);
}
*/
