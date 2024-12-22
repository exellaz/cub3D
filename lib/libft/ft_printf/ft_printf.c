/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:40:17 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/02/29 16:06:47 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*arg_parser(const char *format, va_list args)
{
	const char	*arg_str;

	arg_str = 0;
	if (*(format + 1) == 'c')
		arg_str = char_parser(args);
	else if (*(format + 1) == 's')
		arg_str = str_parser(args);
	else if (*(format + 1) == 'p')
		arg_str = ptr_parser(args);
	else if (*(format + 1) == 'd')
		arg_str = decimal_parser(args);
	else if (*(format + 1) == 'i')
		arg_str = decimal_parser(args);
	else if (*(format + 1) == 'u')
		arg_str = unsigned_parser(args);
	else if (*(format + 1) == 'x')
		arg_str = low_hexa_parser(args);
	else if (*(format + 1) == 'X')
		arg_str = up_hexa_parser(args);
	else if (*(format + 1) == '%')
		arg_str = ft_strdup("%");
	return (arg_str);
}

static size_t	specifier_strlen(const char *s, char specifier)
{
	size_t	size;

	if (specifier == 'c')
		return (1);
	size = 0;
	while (s[size] != 0)
		size++;
	return (size);
}

static void	putstr(char *s, char specifier)
{
	int	i;

	if (specifier == 'c' && *s == 0)
	{
		ft_putchar_fd(*s, 1);
		return ;
	}
	if (s == NULL)
		return ;
	i = -1;
	while (s[++i] != 0)
		ft_putchar_fd(s[i], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	const char	*parsed_arg;
	int			len;
	int			i;

	va_start(args, format);
	len = 0;
	i = -1;
	while (format[++i] != 0)
	{
		if (format[i] == '%')
		{
			parsed_arg = arg_parser(format + i++, args);
			len += specifier_strlen(parsed_arg, *(format + i));
			putstr((char *)parsed_arg, *(format + i));
			free((void *)parsed_arg);
		}
		else
		{
			++len;
			write(1, format + i, 1);
		}
	}
	va_end(args);
	return (len);
}
