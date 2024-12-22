/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:49:28 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 12:35:36 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digits(long n)
{
	size_t	digits;

	if (n == -2147483647 - 1)
		return (10);
	digits = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		++digits;
	}
	return (digits);
}

static void	*mem_alloc(char **num_str, long *num, size_t digits, int *i)
{
	if (*num >= 0)
	{
		*num_str = (char *)malloc((digits + 1) * sizeof(char));
		if (*num_str == NULL)
			return (NULL);
	}
	else
	{
		*num_str = (char *)malloc((1 + digits + 1) * sizeof(char));
		if (*num_str == NULL)
			return (NULL);
		*num_str[(*i)++] = '-';
		*num = -(*num);
	}
	return ((void *)1);
}

static int	count_tens(size_t digits)
{
	int	tens;
	int	i;

	tens = 1;
	i = 0;
	while (++i < (int)digits)
		tens *= 10;
	return (tens);
}

char	*ft_itoa(int n)
{
	char	*num_str;
	long	num;
	size_t	digits;
	int		tens;
	int		i;

	num = (long)n;
	digits = count_digits(num);
	i = 0;
	if (mem_alloc(&num_str, &num, digits, &i) == NULL)
		return (NULL);
	tens = count_tens(digits);
	while (tens > 0)
	{
		num_str[i++] = (num / tens) - ((num / tens) - (num / tens % 10)) + '0';
		tens /= 10;
	}
	num_str[i] = 0;
	return (num_str);
}

/*
#include <limits.h>

int	main(void)
{
	printf("0 | %s\n", ft_itoa(0));
	printf("9 | %s\n", ft_itoa(9));
	printf("10 | %s\n", ft_itoa(10));
	printf("-10 | %s\n", ft_itoa(-10));
	printf("%d | %s\n", INT_MAX, ft_itoa(INT_MAX));
	printf("%d | %s\n", INT_MIN + 1, ft_itoa(INT_MIN + 1));
	printf("%d | %s\n", INT_MIN, ft_itoa(INT_MIN));
	// ft_itoa(0);	printf("\n");
	// ft_itoa(10);	printf("\n");
	// ft_itoa(INT_MAX);	printf("\n");
	// ft_itoa(INT_MIN + 1);	printf("\n");
	// ft_itoa(INT_MIN);	printf("\n");
}
*/

/*
itoa:

int num = 123456

str_len = 6 + 1(NULL terminator)

		   N	  tens	 extras
byte1: 	123456 / 100000 - 0 = 		1			1 - 0
byte2: 	123456 / 10000 - 10 = 		2			12 - 10
byte3: 	123456 / 1000 - 120 = 		3			123 - 120
byte4: 	123456 / 100 - 	1230 = 		4			1234 - 1230
byte5: 	123456 / 10 - 	12340 = 	5			12345 - 12340
byte6: 	123456 / 1 - 	123450 = 	6			123456 - 123450
byte7:	\0

(N / tens) - (N / tens % 10) 
*/
