/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 08:48:12 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 12:37:27 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(char const *s, char c)
{
	size_t	str_count;
	int		i;

	if (*s == 0)
		return (0);
	str_count = 1;
	i = -1;
	if (s[0] == c)
		--str_count;
	while (s[++i] != 0)
		if (s[i + 1] != 0 && s[i] == c)
			if (!(s[i + 1] == c))
				++str_count;
	return (str_count);
}

static size_t	split_len(char const **s_ptr, char const c)
{
	size_t	len;

	len = 0;
	while (**s_ptr == c)
		++(*s_ptr);
	while (**s_ptr != c && **s_ptr != 0)
	{
		++len;
		++(*s_ptr);
	}
	return (len);
}

static void	putstr(char *str, char const **s_ptr, char const c)
{
	int	i;

	while (**s_ptr == c)
		++(*s_ptr);
	i = -1;
	while (**s_ptr != c && **s_ptr != 0)
	{
		str[++i] = **s_ptr;
		++(*s_ptr);
	}
	str[i + 1] = 0;
}

char	**ft_split(char const *s, char c)
{
	char		**str_array;
	char const	*s_ptr;
	size_t		str_count;
	int			i;

	if (s == NULL || s == 0)
		return (NULL);
	str_count = count_str(s, c);
	str_array = (char **)malloc((str_count + 1) * sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	s_ptr = s;
	i = -1;
	while (++i < (int)str_count)
	{
		str_array[i] = (char *)malloc(split_len(&s_ptr, c) + 1);
		if (str_array[i] == NULL)
			return (NULL);
	}
	str_array[str_count] = 0;
	s_ptr = s;
	i = -1;
	while (++i < (int)str_count)
		putstr(str_array[i], &s_ptr, c);
	return (str_array);
}

/*

int	main(void)
{
	char	c = '|';
	
	printf("1\n");
	char	*s = "12345|67890";
	char	**str_arr = ft_split(s, c);
	char	**sa_ptr = str_arr;
	printf("Before: %s\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");
	
	printf("2\n");
	s = "|1234567890|";
	str_arr = ft_split(s, c);
	sa_ptr = str_arr;
	printf("Before: %s\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");
	
	printf("3\n");
	s = "||||1234567890||||";
	str_arr = ft_split(s, c);
	sa_ptr = str_arr;
	printf("Before: %s\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");
		
	printf("4\n");
	s = "|1234|567890";
	str_arr = ft_split(s, c);
	sa_ptr = str_arr;
	printf("Before: %s\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");
		
	printf("5\n");
	s = "|12345|6789|0";
	str_arr = ft_split(s, c);
	sa_ptr = str_arr;
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");
	
	printf("6\n");
	s = "||||12345|||6789||0";
	str_arr = ft_split(s, c);
	sa_ptr = str_arr;
	printf("Before: %s\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("%s\n", *(sa_ptr++));
	printf("_____________________________________\n");

	printf("7\n");
	s = "";
	str_arr = ft_split(s, 'z');
	sa_ptr = str_arr;
	printf("Before: \"%s\"\nAfter:\n", s);
	while (*sa_ptr != 0)
		printf("\"%s\"\n", *(sa_ptr++));
	printf("_____________________________________\n");
}
*/
