/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:55:41 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 10:04:36 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_texture_paths(t_texture *textures, char *prefix, int max);

void	init_torch_sprites(t_vars *vars)
{
	t_sprite	*sprite;
	t_texture	*textures;

	sprite = ft_calloc(1, sizeof(t_sprite));
	textures = sprite->frame_data;
	sprite->frame_duration = 0.03f;
	get_texture_paths(textures, TORCH_1_PATH, SPRITE_1_FRAME_COUNT);
	load_textures(textures, vars->mlx, SPRITE_1_FRAME_COUNT);
	vars->sprite = sprite;
}

static void	get_texture_paths(t_texture *textures, char *prefix, int max)
{
	char	*num;
	char	*path;
	int		i;

	i = 0;
	while (i < max)
	{
		num = ft_itoa(i + 1);
		path = ft_strjoin(prefix, num);
		path = c_strjoin(&path, ".xpm");
		textures[i].path = path;
		i++;
	}
}
