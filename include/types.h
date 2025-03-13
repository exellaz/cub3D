/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:33:06 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/13 13:54:19 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <time.h>
# include <stdbool.h>

typedef struct s_list		t_list;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		offset;
}	t_img;

typedef struct s_door
{
	int		x;
	int		y;
	bool	is_open;
	float	progress;
}				t_door;

typedef struct s_texture
{
	t_img	*img;
	char	*path;
	int		width;
	int		height;
}	t_texture;

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
	t_door	*first_door;
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
	bool	torch_toggle;
	bool	is_moving;
}	t_player;

typedef struct s_fps
{
	int		frame_count;
	float	frame_time;
	float	fps;
	clock_t	start_time;
	clock_t	last_frame_time;
}				t_fps;

typedef struct s_map
{
	t_list		*map_list;
	char		**map;
	t_texture	*texture_data;
	int			floor_color;
	int			ceiling_color;
	int			*spawn;
	t_door		*doors;
	int			texture_count;
	int			door_count;
	int			width;
	int			height;
	int			tile_size;
	int			**texture;
	int			tex_width;
	int			tex_height;
}	t_map;

typedef struct s_sprite
{
	t_texture	*frame_data;
	int			current_frame;
	float		frame_time;
	float		last_update;
	float		frame_duration;
	float		bob_offset;
	float		sway_offset;
}				t_sprite;

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
	float		max_brightness;
	t_map		*map_data;
	t_sprite	*sprite;
}				t_vars;

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

typedef struct s_fpoint
{
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_floor
{
	t_fpoint	pos;
	t_fpoint	step;
}	t_floor;

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

enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
};

#endif
