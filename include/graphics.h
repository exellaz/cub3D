/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:00:47 by we                #+#    #+#             */
/*   Updated: 2025/01/14 11:04:19 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define BLOCK_SIZE 64
# define PI 3.14159

# include <stdbool.h>
# include <time.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}				t_img;

typedef struct s_player
{
	// float	x;
	// float	y;
	// float	angle;
	// bool	left_rotate;
	// bool	right_rotate;

	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}				t_player;

typedef struct s_fps
{
	int		frame_count;
	float	frame_time;
	float	fps;
	clock_t	start_time;
	clock_t	last_frame_time;
}				t_fps;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	**map;
	t_img	img;
	t_player	*player;
	t_fps	*fps;
}				t_mlx;

typedef struct s_point
{
	float x;
	float y;
}				t_point;


#endif
