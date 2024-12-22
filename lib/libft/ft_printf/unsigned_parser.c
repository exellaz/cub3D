/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:35:22 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/02/29 16:07:36 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*unsigned_parser(va_list args)
{
	char			*parsed_arg;
	unsigned int	arg;

	arg = va_arg(args, unsigned int);
	parsed_arg = ft_itoa(arg);
	return (parsed_arg);
}
