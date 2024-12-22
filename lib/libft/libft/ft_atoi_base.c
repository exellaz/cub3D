/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:38:16 by we                #+#    #+#             */
/*   Updated: 2024/05/10 15:37:01 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_to_dec(const char *nptr);

// Only supports base 16 (positive) for now
int	ft_atoi_base(const char *nptr, int base)
{
	if (base == 2)
		return (0);
	else if (base == 8)
		return (0);
	else if (base == 10)
		return (ft_atoi(nptr));
	else if (base == 16)
		return (hex_to_dec(nptr));
	else
		return (0);
}

static int	hex_to_dec(const char *nptr)
{
	int		decimal;
	int		p_or_n;
	int		len;
	int		i;

	p_or_n = 1;
	decimal = 0;
	nptr = (char *)nptr + 2;
	if (*(nptr - 2) == '-')
	{
		p_or_n = -1;
		nptr += 1;
	}
	len = ft_strlen(nptr) - 1;
	i = -1;
	while (len - ++i > -1)
	{
		if (nptr[len - i] >= '0' && nptr[len - i] <= '9')
			decimal += (nptr[len - i] - '0') * ft_pow(16, i);
		else if (nptr[len - i] >= 'A' && nptr[len - i] <= 'F')
			decimal += (nptr[len - i] - 'A' + 10) * ft_pow(16, i);
		else if (nptr[len - i] >= 'a' && nptr[len - i] <= 'f')
			decimal += (nptr[len - i] - 'a' + 10) * ft_pow(16, i);
	}
	return (p_or_n * decimal);
}
