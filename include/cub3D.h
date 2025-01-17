/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/01/10 09:51:04 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>

# include <mlx.h>
# include <Libft.h>

# include "graphics.h"

int		validate_arg(int argc, char *file);
void	setup_mlx(t_mlx *m, t_player *player);
char	**hardcode_map(void);
int		draw_ray(t_player *player, t_mlx *mlx, float start_x, int i);
void	put_pixel(int x, int y, int color, t_img *img);
int		frame_counter(t_fps *fps);

#endif
