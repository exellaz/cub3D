/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:32:00 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/02/29 16:07:23 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	decimal_to_hexa(unsigned long long decimal, char *parsed_arg)
{
	int		i;

	i = -1;
	while (decimal != 0)
	{
		if (decimal % 16 >= 10)
			parsed_arg[++i] = decimal % 16 + 'a' - 10;
		else
			parsed_arg[++i] = decimal % 16 + '0';
		decimal /= 16;
	}
	parsed_arg[i + 1] = 0;
	reverse_arr(parsed_arg);
}

const char	*ptr_parser(va_list args)
{
	char				*parsed_arg;
	unsigned long long	arg;

	arg = va_arg(args, unsigned long long);
	if (arg == 0)
		return (ft_strdup("0x0"));
	parsed_arg = (char *)malloc(64 * sizeof(char));
	if (parsed_arg == NULL)
		return (NULL);
	*parsed_arg = 0;
	ft_strlcpy(parsed_arg, "0x", 64);
	decimal_to_hexa(arg, parsed_arg + 2);
	return (parsed_arg);
}
