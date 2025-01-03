/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:00:47 by we                #+#    #+#             */
/*   Updated: 2025/01/03 19:22:13 by kkhai-ki         ###   ########.fr       */
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
	int	x;
	int	y;
}				t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	**map;
	t_img	img;
	t_player	*player;
}				t_mlx;

#endif
