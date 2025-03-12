/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:44:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 11:03:04 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include <math.h>
# include "types.h"
# include "defines.h"
# include "utils.h"

void		render_minimap(t_player *player, t_vars *vars, t_map *map_data);
void		draw_player(t_player *player, float map_x, \
				float map_y, t_vars *vars);
int			get_minimap_range(t_map *map_data);
int			calculate_opacity(int tile_size, t_fpoint pixel, t_player *player);
int			*get_tile_texture(t_point tile, char **map, \
				int tex_count, int **textures);

#endif