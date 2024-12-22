/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:55:44 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/23 15:20:11 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	p_or_n;

	num = 0;
	p_or_n = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\t' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r' || *nptr == '\n'
		|| *nptr == '\f')
		nptr++;
	if (*nptr == '-')
	{
		p_or_n = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (num * p_or_n);
}

/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	s1[] = "12345";
	char	s2[] = "	 12345";
	char	s3[] = "	 123aaa45";
	char	s4[] = "	 aaa123aaa45";
	char	s5[] = "-12345";
	char	s6[] = "--12345";
	char	s7[] = "+12345";
	char	s8[] = "-+12345";
	char	s9[] = "+-12345";
	char	s10[] = " - 12345";
	
	printf("original:\n");
	printf("\"%s\": %d\n", s1, atoi(s1));
	printf("\"%s\": %d\n", s2, atoi(s2));
	printf("\"%s\": %d\n", s3, atoi(s3));
	printf("\"%s\": %d\n", s4, atoi(s4));
	printf("\"%s\": %d\n", s5, atoi(s5));
	printf("\"%s\": %d\n", s6, atoi(s6));
	printf("\"%s\": %d\n", s7, atoi(s7));
	printf("\"%s\": %d\n", s8, atoi(s8));
	printf("\"%s\": %d\n", s9, atoi(s9));
	printf("\"%s\": %d\n", s10, atoi(s10));
	printf("\n");
	printf("ft_:\n");
	printf("\"%s\": %d\n", s1, ft_atoi(s1));
	printf("\"%s\": %d\n", s2, ft_atoi(s2));
	printf("\"%s\": %d\n", s3, ft_atoi(s3));
	printf("\"%s\": %d\n", s4, ft_atoi(s4));
	printf("\"%s\": %d\n", s5, ft_atoi(s5));
	printf("\"%s\": %d\n", s6, ft_atoi(s6));
	printf("\"%s\": %d\n", s7, ft_atoi(s7));
	printf("\"%s\": %d\n", s8, ft_atoi(s8));
	printf("\"%s\": %d\n", s9, ft_atoi(s9));
	printf("\"%s\": %d\n", s10, ft_atoi(s10));

}
*/
