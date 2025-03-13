/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils-1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:45 by we                #+#    #+#             */
/*   Updated: 2025/03/13 14:11:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <c_libft.h>

#include "utils.h"
#include "error.h"
#include "map.h"

// takes a file descriptor as argument and returns a 2D array of strings
t_list	*load_file(int file)
{
	t_list	*map;
	char	*line;

	map = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_lstadd_back(&map, ft_lstnew(line));
		line = get_next_line(file);
	}
	if (!map)
		error_exit("Empty file");
	close(file);
	return (map);
}

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
	return (split);
}
