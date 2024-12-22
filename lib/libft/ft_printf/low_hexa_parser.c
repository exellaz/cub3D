/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_hexa_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:50 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/02/29 16:07:19 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reverse_arr(char *hexa)
{
	char	temp;
	int		size;
	int		i;

	size = ft_strlen(hexa);
	i = -1;
	while (++i < size / 2)
	{
		temp = hexa[i];
		hexa[i] = hexa[size - i - 1];
		hexa[size - i - 1] = temp;
	}
}

static void	decimal_to_hexa(unsigned int decimal, char *parsed_arg)
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

const char	*low_hexa_parser(va_list args)
{
	char			*parsed_arg;
	unsigned int	arg;

	arg = va_arg(args, unsigned int);
	if (arg == 0)
		return (ft_strdup("0"));
	parsed_arg = (char *)malloc(64 * sizeof(char));
	if (parsed_arg == NULL)
		return (NULL);
	*parsed_arg = 0;
	decimal_to_hexa(arg, parsed_arg);
	return (parsed_arg);
}
