/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/02/09 13:51:40 by kkhai-ki         ###   ########.fr       */
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

int		validate_arg(int argc, char *file);
void	init_vars(t_vars *vars, int fd);
int		draw_ray(t_player *player, t_vars *mlx, float start_x, int i);
void	put_pixel(int x, int y, int color, t_img *img);
int		frame_counter(t_fps *fps);
void	render_minimap(t_player *player, t_vars *vars, t_map *map_data);
void	draw_border(int x, int y, int size, int border_thickness, int border_color, t_img *img); //Refactor to 4 param
void	draw_tile(int x, int y, int size, int color, t_img *img);
int		mouse_hook(int x, int y, t_vars *vars);
void	handle_player_controls(t_player *player, t_fps *fps, t_map *map_data);


#endif
