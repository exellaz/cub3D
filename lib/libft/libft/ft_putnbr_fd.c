/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:01:42 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 12:36:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_tens1(long n)
{
	int		tens;

	tens = 1;
	while (n >= 10)
	{
		tens *= 10;
		n /= 10;
	}
	return (tens);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	int		tens;

	if (n == -2147483647 - 1)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	tens = count_tens1((long)n);
	while (tens >= 1)
	{
		num = n / tens % 10 + '0';
		tens /= 10;
		write(fd, &num, 1);
	}
}

/*
#include <limits.h>

int	main(void)
{
	ft_putnbr_fd(0, 1);	printf("\n");
	ft_putnbr_fd(5, 1);	printf("\n");
	ft_putnbr_fd(10, 1); printf("\n");
	ft_putnbr_fd(INT_MAX, 1); printf("\n");
	ft_putnbr_fd(INT_MIN + 1, 1); printf("\n");
	ft_putnbr_fd(INT_MIN, 1); printf("\n");
}
*/
