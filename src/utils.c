/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:23:53 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/10 09:57:36 by tjun-yu          ###   ########.fr       */
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
		arr[++i] = lst->content;
		arr[i][ft_strlen(arr[i]) - 1] = '\0';
		lst = lst->next;
	}
	arr[++i] = NULL;
	return (arr);
}

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
