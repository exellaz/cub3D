/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/03/12 09:57:36 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <time.h>
# include <X11/keysym.h>
# include <Libft.h>

# include "defines.h"
# include "map.h"

// Player Controls
void		handle_player_controls(t_player *player, t_fps *fps, \
				t_map *map_data, t_vars *vars);
void		rotate_player(float angle, t_player *player);

// Event Handlers
void		handle_toggles(int keycode, t_player *player, t_vars *vars);
void		handle_movement(int keycode, t_player *player, bool state);
void		handle_interact(t_player *player, t_map *map_data);
int			quit(int keycode, t_vars *vars);

// Event Hooks
int			mouse_hook(int x, int y, t_vars *vars);
int			key_release_hook(int keycode, t_vars *vars);
int			key_press_hook(int keycode, t_vars *vars);

// Raycaster
void		raycast(t_vars *vars);
void		render_walls(t_vars *vars, t_player *player, t_map *map_data);
void		render_open_door(t_vars *vars, int x);
void		render_floor_and_ceiling(t_vars *vars, \
				t_player *player, t_map *map_data);
void		draw_floor_and_ceiling_row(float row_distance, t_floor *floor, \
				t_vars *vars, t_point window);
t_tex_data	get_tex_data(int x, t_ray *ray, t_player *player, t_vars *vars);
void		draw_textured_column(int x, t_ray *ray, \
				t_tex_data *tex_data, t_vars *vars);
void		init_ray(int x, t_player *player, t_ray *ray);
void		find_step_and_dist(t_ray *ray, t_player *player);

// Minimap
void		render_minimap(t_player *player, t_vars *vars, t_map *map_data);
void		draw_player(t_player *player, float map_x, \
				float map_y, t_vars *vars);

// Frame Counter
void		init_fps(t_vars *vars);
int			frame_counter(t_fps *fps);

// Pixel Utils
void		put_pixel(int x, int y, int color, t_img *img);
int			apply_opacity(int color, int opacity_int);

// Setup
void		init_vars(t_vars *vars, int fd);
int			validate_arg(int argc, char *file);

// Doors
t_door		*find_door(t_map *map_data, int x, int y);
void		update_doors(t_map *map_data);

// Sprites
void		render_sprite(t_vars *vars, t_sprite *sprite);

#endif
