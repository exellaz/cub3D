/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:04:47 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/20 11:39:08 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
    char c, result;

    c = 'M';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    c = 'm';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    c = '+';
    result = ft_tolower(c);
    printf("ft_tolower(%c) = %c\n", c, result);

    return 0;
}
*/
