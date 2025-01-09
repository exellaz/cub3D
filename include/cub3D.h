/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2025/01/09 12:30:44 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>

# include <mlx.h>
# include <Libft.h>

# include "graphics.h"

void	setup_mlx(t_mlx *m, t_player *player);
char	**get_map(void);
int		draw_ray(t_player *player, t_mlx *mlx, float start_x, int i);
void	put_pixel(int x, int y, int color, t_img *img);
int		frame_counter(t_fps *fps);

#endif
