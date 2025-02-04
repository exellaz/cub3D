/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:00:47 by we                #+#    #+#             */
/*   Updated: 2025/02/04 15:15:13 by kkhai-ki         ###   ########.fr       */
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

# define BLOCK_SIZE 32
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MINIMAP_SIZE 360
# define MINIMAP_OFFSET 4
# define VISIBLE_RANGE 4
# define PI 3.14159
# define MOUSE_SPEED 0.0005

# include <stdbool.h>
# include <time.h>
# include <X11/keysym.h>

typedef struct s_list	t_list;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}				t_img;

typedef struct s_ray
{
	float	camera_x;
	float	dir_x;
	float	dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	float	perp_wall_dist;
	int		wall_side;
	int		draw_start;
	int		draw_end;
	int		line_height;
}				t_ray;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	bool	move_forward;
	bool	move_backward;
	bool	move_left;
	bool	move_right;
	bool	pan_left;
	bool	pan_right;
	bool	interact;
	bool	interact_held;
	t_ray	ray;
}				t_player;

typedef struct s_fps
{
	int		frame_count;
	float	frame_time;
	float	fps;
	clock_t	start_time;
	clock_t	last_frame_time;
}				t_fps;

typedef struct s_door
{
	int		x;
	int		y;
	bool	is_open;
}				t_door;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	char		**map;
	t_player	*player;
	t_fps		*fps;
	int			**texture;
	int			map_width;
	int			map_height;
	int			tile_size;
	bool		mouse_move;
	int			prev_mouse_x;
	int			prev_mouse_y;
	bool		minimap_toggle;
	t_door		*doors;
}				t_vars;

typedef struct s_point
{
	float x;
	float y;
}				t_point;

#endif
