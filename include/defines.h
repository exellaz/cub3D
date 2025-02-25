/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:42:39 by we                #+#    #+#             */
/*   Updated: 2025/02/25 11:12:35 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <time.h>
# include "map.h"
# include "utils.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define BLOCK_SIZE 32
# define TEX_WIDTH 32
# define TEX_HEIGHT 32
# define MINIMAP_SIZE 360
# define MINIMAP_OFFSET 4
# define VISIBLE_RANGE 4
# define PI 3.14159
# define MOUSE_SPEED 0.0005
# define CURSOR_COLOR 0xFF000

typedef struct s_list	t_list;
typedef struct s_map	t_map;

typedef struct s_tex_data
{
	int		tex_num;
	int		tex_x;
	int		tex_y;
	float	wall_x;
	float	step;
	float	tex_pos;
	float	base_opacity;
}				t_tex_data;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}				t_img;

typedef struct s_door
{
	int		x;
	int		y;
	bool	is_open;
	float	progress;
}				t_door;

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
	t_door	*door;
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
	t_map		*map_data;
}				t_vars;

typedef struct s_fpoint
{
	float x;
	float y;
}				t_fpoint;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

enum e_keycode
{
	KEY_ESC = 0,
	KEY_W = 1,
	KEY_A = 2,
	KEY_S = 3,
	KEY_D = 4,
	KEY_M = 5,
	KEY_LEFT = 7,
	KEY_RIGHT = 8
};

enum e_event
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	BUTTON_PRESS = 4,
	BUTTON_RELEASE = 5,
	MOTION_NOTIFY = 6,
	CREATE_NOTIFY = 16,
	DESTROY_NOTIFY = 17,
	RESIZE_REQUEST = 25,
	GENERIC_EVENT = 35,
	LAST_EVENT = 36
};

enum e_mask
{
	NOT_EVENT_MASK = 0L,
	KEY_PRESS_MASK = 1L<<0,
	KEY_RELEASE_MASK = 1L<<1,
	BUTTON_PRESS_MASK = 1L<<2,
	BUTTON_RELEASE_MASK = 1L<<3,
	POINTER_MOTION_MASK = 1L<<6,
};

enum	e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	DOOR
};

#endif
