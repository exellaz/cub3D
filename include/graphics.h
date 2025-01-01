/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:00:47 by we                #+#    #+#             */
/*   Updated: 2025/01/01 18:06:17 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
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

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

#endif
