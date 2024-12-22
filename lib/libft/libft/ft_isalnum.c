/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:50:50 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:35:42 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", isalnum('1'));
	printf("%d\n", isalnum('a'));
	printf("%d\n", isalnum('A'));
	printf("\n");
	printf("%d\n", ft_isalnum('1'));
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('A'));
}
*/
