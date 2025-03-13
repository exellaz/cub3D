/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:07 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/13 14:11:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <X11/keysym.h>
# include <mlx.h>
# include <math.h>
# include <c_libft.h>
# include "utils.h"
# include "types.h"
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

#endif
