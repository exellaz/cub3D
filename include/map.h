/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:54:34 by we                #+#    #+#             */
/*   Updated: 2024/12/27 15:57:15 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_list	t_list;

// `texture` is stored in N, S, E, W order
// `ceiling` and `floor` are stored in R, G, B order
// `texture` and `rgb` are optional
typedef struct s_map
{
	t_list	*map;
	char	*texture_path[4];
	int		ceiling_rgb[3];
	int		floor_rgb[3];
}	t_map;

t_map	*parse_map(int file);
t_list	*load_file(int file);
t_list	*get_texture_path(t_list *raw, char **texture_path);
t_list	*get_rgb(t_list *raw, int *rgb);
int		get_map(t_list *raw, t_list **map);

#endif
