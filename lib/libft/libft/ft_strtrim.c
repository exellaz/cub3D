/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:53:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 12:31:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	is_set(char const c, char const *set)
{
	while (*set != 0)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	trim_start_size(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (is_set(s1[start], set) && s1[start] != 0)
		++start;
	return (start);
}

static int	trim_end_size(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (is_set(s1[end], set) && end > -1)
		--end;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed_str;
	int		start;
	int		end;
	int		i;

	if (s1 == NULL)
		return (NULL);
	start = trim_start_size(s1, set);
	if (start == (int)ft_strlen(s1))
		return (ft_strdup(""));
	end = trim_end_size(s1, set);
	trimed_str = (char *)malloc(end - start + 2);
	if (trimed_str == NULL)
		return (NULL);
	i = -1;
	while (&(s1[start]) != &(s1[end + 1]))
	{
		trimed_str[++i] = s1[start];
		++start;
	}
	trimed_str[i + 1] = 0;
	return (trimed_str);
}

/*
int main(void)
{
	char	*s1 = "111abcd234";
	char	*set1 = "1234";
	printf("Original string: \"%s\"\n", s1);
	printf("Trimmed string: \"%s\"\n\n", ft_strtrim(s1,set1));

	char	*s2 = "lorem ipsum dolor sit amet";
	char	*set2 = "te";
	printf("Original string: \"%s\"\n", s2);
	printf("Trimmed string: \"%s\"\n\n", ft_strtrim(s2, set2));

	char	*s3 = "          ";
	char	*set3 = " ";
	printf("Original string: \"%s\"\n", s3);
	printf("Trimmed string: \"%s\"\n", ft_strtrim(s3,set3));
}
*/