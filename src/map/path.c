/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:02:19 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/03/12 13:24:06 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>

#include "error.h"
#include "map.h"

static void	get_path(t_list **raw, t_texture *texture, int count);
static bool	get_wall_path(char **split, t_texture *texture);
static bool	get_opt_path(char **split, t_texture *texture);
static void	check_path(t_texture *texture, int count);

t_list	*get_texture_path(t_list *raw, t_texture *texture, int *count)
{
	t_list	*tmp;
	int		i;

	i = -1;
	while (++i < 7)
		texture[i].path = NULL;
	raw = skip_empty_lines(raw);
	*count = 0;
	tmp = raw;
	while (!is_whitespace(((char *)tmp->content)[0]))
	{
		*count += 1;
		tmp = tmp->next;
	}
	get_path(&raw, texture, *count);
	if (*count < 4 || *count > 7)
		error_exit("Invalid texture count");
	return (raw->next);
}

static void	get_path(t_list **raw, t_texture *texture, int count)
{
	char	**split;
	int		i;

	i = -1;
	while (++i < count)
	{
		split = split_cfg((*raw)->content);
		if (get_wall_path(split, texture))
			;
		else if (get_opt_path(split, texture))
			;
		else
			error_exit("Invalid texture identifier");
		*raw = (*raw)->next;
	}
	check_path(texture, count);
}

static bool	get_wall_path(char **split, t_texture *texture)
{
	if (ft_strcmp(split[0], "NO") == 0)
		texture[0].path = split[1];
	else if (ft_strcmp(split[0], "SO") == 0)
		texture[1].path = split[1];
	else if (ft_strcmp(split[0], "WE") == 0)
		texture[2].path = split[1];
	else if (ft_strcmp(split[0], "EA") == 0)
		texture[3].path = split[1];
	else
		return (false);
	return (true);
}

static bool	get_opt_path(char **split, t_texture *texture)
{
	if (ft_strcmp(split[0], "FL") == 0)
		texture[4].path = split[1];
	else if (ft_strcmp(split[0], "CL") == 0)
		texture[5].path = split[1];
	else if (ft_strcmp(split[0], "DO") == 0)
		texture[6].path = split[1];
	else
		return (false);
	return (true);
}

static void	check_path(t_texture *texture, int count)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (!texture[i].path)
			error_exit("Missing wall texture paths");
	if (count == 6 || count == 7)
		if (texture[4].path == NULL || texture[5].path == NULL)
			error_exit("Missing floor or ceiling texture");
	if (count == 5 || count == 7)
		if (!texture[6].path)
			error_exit("Missing door texture");
}
