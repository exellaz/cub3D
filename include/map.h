/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:54:34 by we                #+#    #+#             */
/*   Updated: 2024/12/24 15:59:57 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_list	t_list;

// `texture` is stored in N, S, E, W order
typedef struct s_map
{
	t_list	*map;
	char	*texture_path[4];
	int		ceiling_rgb[3];
	int		floor_rgb[3];
}	t_map;

t_list	*load_file(int file);
char	*parse_texture(char *line);
int		*parse_rgb(char *line);

#endif
