/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:45 by we                #+#    #+#             */
/*   Updated: 2025/02/04 16:15:58 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <Libft.h>

#include "utils.h"
#include "error.h"
#include "map.h"

void	count_cfg(t_list *raw, int count, char *msg)
{
	t_list	*tmp;
	int		i;

	raw = skip_empty_lines(raw);
	i = 0;
	tmp = raw;
	while (!is_whitespace(((char *)tmp->content)[0]))
	{
		i += 1;
		tmp = tmp->next;
	}
	if (i != count)
		error_exit(msg);
}

char	**split_cfg(char *line)
{
	char	**split;
	char	**tmp;

	tmp = ft_split(line, '\n');
	split = ft_split(tmp[0], ' ');
	if (!split)
		error_exit(strerror(errno));
	mem_free_arr(tmp);
	return (split);
}
