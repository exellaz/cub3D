/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:00:47 by we                #+#    #+#             */
/*   Updated: 2025/03/05 20:53:09 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>
# include <time.h>
# include <math.h>
# include "map.h"

int				apply_opacity(int color, int opacity);
void			put_pixel(int x, int y, int color, t_img *img);
void			draw_textured_column(int x, t_ray *ray, t_tex_data *tex_data, t_vars *vars);
// void			get_tex_data(int x, t_ray *ray, t_player *player, t_vars *mlx);

#endif
