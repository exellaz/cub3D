/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:30:39 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/13 13:17:03 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include "defines.h"
# include "types.h"
# include "utils.h"

void		raycast(t_vars *vars);
void		render_walls(t_vars *vars, t_player *player, t_map *map_data);
void		render_open_door(t_vars *vars, int x);
void		render_floor_and_ceiling(t_vars *vars, \
				t_player *player);
void		draw_floor_and_ceiling_row(float row_distance, t_floor *floor, \
				t_vars *vars, t_point window);
void		draw_textured_column(int x, t_ray *ray, \
				t_tex_data *tex_data, t_vars *vars);
void		init_ray(int x, t_player *player, t_ray *ray);
void		find_step_and_dist(t_ray *ray, t_player *player);
t_tex_data	get_tex_data(t_ray *ray, t_player *player, t_vars *vars);
t_door		*find_door(t_map *map_data, int x, int y);

#endif