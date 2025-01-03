/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:54:34 by we                #+#    #+#             */
/*   Updated: 2025/01/03 15:02:35 by tjun-yu          ###   ########.fr       */
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
	int		fc_rgb[2][3];
}	t_map;

t_map	*parse_map(int file);
t_list	*load_file(int file);
t_list	*get_texture_path(t_list *raw, char **texture_path);
t_list	*get_rgb(t_list *raw, int (*rgb)[3]);
int		get_map(t_list *raw, t_list **map);

#endif
