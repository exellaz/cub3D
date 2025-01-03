/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:23:53 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/03 14:26:03 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "utils.h"

t_list	*skip_empty_lines(t_list *raw)
{
	while (((char *)raw->content)[0] == '\n')
		raw = raw->next;
	return (raw);
}

bool	is_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
