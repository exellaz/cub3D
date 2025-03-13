/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:42:39 by we                #+#    #+#             */
/*   Updated: 2025/03/13 14:02:17 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define PI 3.14159
# define VISIBLE_RANGE 4
# define MOUSE_SPEED 0.0005
# define MAX_TEX_COUNT 7

// Default: 0.66f
# define FOV 0.66f

// Colors
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

// Minimap
# define MINIMAP_SIZE 360
# define MINIMAP_OFFSET 4
# define MARKER_COLOR 0xFF000

// Sprites
# define SPRITE_SCALE 4
# define SPRITE_1_FRAME_COUNT 80
# define TORCH_1_X 1120
# define TORCH_1_Y 480
# define TORCH_2_X 1320
# define TORCH_2_Y 230
# define TORCH_1_PATH "./assets/minecraft-torch/Torch"
# define TORCH_2_PATH "./assets/real-torch/torch"
# define BOB_SPEED 15.0f

# ifndef FULLBRIGHT
#  define FULLBRIGHT 0
# endif

#endif
