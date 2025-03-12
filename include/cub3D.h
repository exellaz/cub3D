/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/03/12 08:32:26 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include <Libft.h>

# include "defines.h"
# include "graphics.h"
# include "map.h"

void	rotate_player(float angle, t_player *player);
void	handle_player_controls(t_player *player, t_fps *fps, \
			t_map *map_data, t_vars *vars);
void	render_open_door(t_vars *vars, int x);
void	draw_textured_column(int x, t_ray *ray, \
			t_tex_data *tex_data, t_vars *vars);
void	handle_toggles(int keycode, t_player *player, t_vars *vars);
void	handle_movement(int keycode, t_player *player, bool state);
void	handle_interact(t_player *player, t_map *map_data);
int		quit(int keycode, t_vars *vars);
int		mouse_hook(int x, int y, t_vars *vars);
int		key_release_hook(int keycode, t_vars *vars);
int		key_press_hook(int keycode, t_vars *vars);
void	draw_floor_and_ceiling_row(float row_distance, t_floor *floor, \
						t_vars *vars, t_point window);
void	floor_casting(t_vars *vars, t_player *player, t_map *map_data);
void	init_fps(t_vars *vars);
int		frame_counter(t_fps *fps);
t_tex_data	get_tex_data(int x, t_ray *ray, t_player *player, t_vars *vars);
void	draw_player(t_player *player, float map_x, float map_y, t_vars *vars);
void	render_minimap(t_player *player, t_vars *vars, t_map *map_data);
void	put_pixel(int x, int y, int color, t_img *img);
void	raycast(t_vars *vars);
void	init_ray(int x, t_player *player, t_ray *ray);
void	find_step_and_dist(t_ray *ray, t_player *player);
void	init_vars(t_vars *vars, int fd);
void	render_sprite(t_vars *vars, t_sprite *sprite);
int	check_door_hit(t_ray *ray, t_map *map_data);
void	get_closed_door_height(t_ray *ray);
int		validate_arg(int argc, char *file);

#endif
