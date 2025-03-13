/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/03/13 14:11:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <c_libft.h>
# include <mlx.h>

# include "defines.h"
# include "types.h"
# include "map.h"
# include "events.h"

// Frame Counter
void		init_fps(t_vars *vars);
int			frame_counter(t_fps *fps);

// Setup
void		init_vars(t_vars *vars, int fd);
int			validate_arg(int argc, char *file);

// Main
void		raycast(t_vars *vars);
void		update_doors(t_map *map_data);
void		render_sprite(t_vars *vars, t_sprite *sprite);
void		render_minimap(t_player *player, t_vars *vars, t_map *map_data);

#endif
