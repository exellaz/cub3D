/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:54:34 by we                #+#    #+#             */
/*   Updated: 2025/02/13 11:06:42 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "defines.h"

# define VALID_IDEN " 01NSEWD"

typedef struct s_list	t_list;
typedef struct s_img	t_img;
typedef struct s_door	t_door;

typedef struct s_texture
{
	t_img	*img;
	char	*path;
	int		width;
	int		height;
}	t_texture;

// `texture` is stored in N, S, E, W, D order
// `floor` and `ceiling` are stored in R, G, B order
// `spawn` is stored in x, y, direction order
// `door` is stored in x, y order
typedef struct s_map
{
	t_list		*map;
	t_texture	texture[5];
	int			fc_rgb[2][3];
	int			spawn[3];
	t_door		*door;
	int			texture_count;
	int			door_count;
	int			width;
	int			height;
}	t_map;

t_map	*parse_map(int file, void *mlx);
t_list	*load_file(int file);
t_list	*get_texture_path(t_list *raw, t_texture *texture, int *count);
t_list	*get_rgb(t_list *raw, int (*rgb)[3]);
void	get_map(t_list *raw, t_list **map, int *width, int *height);
void	get_spawn(t_list *map, int *spawn);
void	get_doors(t_list *map, t_door **door, int *count);
void	load_textures(t_texture *texture, void *mlx, int count);
void	free_texture(t_texture *texture, void *mlx, int count);

void	valid_texture_path(t_texture *texture);
void	valid_iden(t_list *map);
void	valid_walls(t_list *map, int height);

void	count_cfg(t_list *raw, int count, char *msg);
char	**split_cfg(char *line);

void	print_texture_path(t_texture *texture);
void	print_rgb(int (*rgb)[3]);
void	print_spawn(int *spawn);
void	print_map(t_list *map);

#endif
