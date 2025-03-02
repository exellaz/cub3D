/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazzite <bazzite@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:23:53 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/02/26 21:20:28 by bazzite          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "utils.h"

char	**lst_to_arr(t_list *lst)
{
	char	**arr;
	int		i;

	arr = (char **)mem_alloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = -1;
	while (lst)
	{
		arr[++i] = ft_strdup(lst->content);
		lst = lst->next;
	}
	arr[++i] = NULL;
	return (arr);
}

t_list	*skip_empty_lines(t_list *raw)
{
	int	i;

	while (((char *)raw->content))
	{
		i = -1;
		while (((char *)raw->content)[++i])
			if (!is_whitespace(((char *)raw->content)[i]))
				return (raw);
		if (raw->next == NULL)
			return (raw);
		raw = raw->next;
	}
	return (raw);
}

bool	is_whitespace(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

bool	is_num(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	print_arr(char **arr)
{
	while (*arr)
	{
		ft_putendl_fd(*arr, 1);
		arr++;
	}
}
