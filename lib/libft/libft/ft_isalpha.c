/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:15:10 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:35:56 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z'))
		return (0);
	return (1);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("%d\n", isalpha('b'));
	printf("%d\n", isalpha('z'));
	printf("%d\n", isalpha('1'));
	// printf("%d\n", isalpha("aa"));

	printf("%d\n", ft_isalpha('z'));
	printf("%d\n", ft_isalpha('b'));
	printf("%d\n", ft_isalpha('1'));
	// printf("%d\n", isalpha("aa"));
}
*/
