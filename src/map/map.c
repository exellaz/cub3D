/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:17:08 by we                #+#    #+#             */
/*   Updated: 2025/02/06 14:35:20 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <Libft.h>

#include "error.h"
#include "utils.h"
#include "graphics.h"
#include "map.h"

t_map	*parse_map(int file,  void *mlx)
{
	t_map	*map;
	t_list	*raw;
	t_list	*remain;

	map = mem_alloc(sizeof(t_map));
	raw = load_file(file);
	remain = get_texture_path(raw, map->texture);
	remain = get_rgb(remain, map->fc_rgb);
	get_map(remain, &map->map, &map->width, &map->height);
	get_spawn(map->map, map->spawn);
	get_doors(map->map, &map->door, &map->door_count);
	validate_map(map);
	load_textures(map->texture, mlx);
	close(file);
	return (map);
}

// takes a file descriptor as argument and returns a 2D array of strings
t_list	*load_file(int file)
{
	t_list	*map;
	char	*line;

	map = NULL;
	line = get_next_line(file);
	while (line)
	{
		ft_lstadd_back(&map, ft_lstnew(line));
		line = get_next_line(file);
	}
	if (!map)
		error_exit("Empty file");
	return (map);
}

t_list	*get_texture_path(t_list *raw, t_texture *texture)
{
	char	**split;
	int		i;

	count_cfg(raw, 4, "Texture count is not 4");
	i = -1;
	while (++i < 4)
	{
		split = split_cfg(raw->content);
		if (ft_strcmp(split[0], "NO") == 0)
			texture[0].path = split[1];
		else if (ft_strcmp(split[0], "SO") == 0)
			texture[1].path = split[1];
		else if (ft_strcmp(split[0], "WE") == 0)
			texture[2].path = split[1];
		else if (ft_strcmp(split[0], "EA") == 0)
			texture[3].path = split[1];
		else
			error_exit("Invalid texture identifier");
		raw = raw->next;
	}
	i = -1;
	while (++i < 4)
		if (!texture[i].path)
			error_exit("Missing texture path");
	return (raw->next);
}

t_list	*get_rgb(t_list *raw, int (*rgb)[3])
{
	char	**split;
	int		fc;
	int		i;
	int		j;

	count_cfg(raw, 2, "RGB count is not 2");
	i = -1;
	while (++i < 2)
	{
		split = split_cfg(raw->content);
		if (count_arr(split) != 2)
			error_exit("RGB count is not 2");
		if (ft_strcmp(split[0], "F") == 0)
			fc = 0;
		else if (ft_strcmp(split[0], "C") == 0)
			fc = 1;
		else
			error_exit("Invalid RGB identifier");
		split = ft_split(split[1], ',');
		if (count_arr(split) != 3)
			error_exit("RGB value count is not 3");
		j = -1;
		while (++j < 3)
		{
			if (!is_num(split[j]))
				error_exit("non-numeric RGB value");
			rgb[fc][j] = ft_atoi(split[j]);
			if (rgb[fc][j] < 0 || rgb[fc][j] > 255)
				error_exit("Invalid RGB value");
		}
		raw = raw->next;
	}
	return (raw);
}

void	get_map(t_list *raw, t_list **map, int *width, int *height)
{
	t_list	*tmp;
	char	*line;
	int		max;
	int		i;

	*map = skip_empty_lines(raw);
	max = 0;
	tmp = *map;
	while (tmp)
	{
		((char *)tmp->content)[ft_strlen(tmp->content) - 1] = '\0';
		if (ft_strlen(tmp->content) > (size_t)max)
			max = ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	*width = max;
	i = -1;
	*height = 0;
	tmp = *map;
	while (tmp)
	{
		if (ft_strlen(tmp->content) < (size_t)max)
		{
			line = mem_alloc(max + 1);
			ft_strlcpy(line, (char *)tmp->content, max + 1);
			i = ft_strlen(line);
			while (i < max)
				line[i++] = ' ';
			line[max] = '\0';
			tmp->content = line;
		}
		*height += 1;
		tmp = tmp->next;
	}
}

void	get_spawn(t_list *map, int *spawn)
{
	char	*line;
	int		i;
	int		j;

	map = skip_empty_lines(map);
	i = -1;
	while (map)
	{
		i += 1;
		line = map->content;
		j = -1;
		while (line[++j])
		{
			if (line[j] == 'N' || line[j] == 'S'
				|| line[j] == 'E' || line[j] == 'W')
			{
				spawn[0] = i;
				spawn[1] = j;
				spawn[2] = line[j];
				return ;
			}
		}
		map = map->next;
	}
}

void	get_doors(t_list *map, t_door **door, int *count)
{
	t_list	*tmp;
	int		i;
	int		j;
	int		k;

	tmp = map;
	i = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->content, 'D'))
			i++;
		tmp = tmp->next;
	}
	*door = mem_alloc(sizeof(t_door) * i);
	*count = i;
	tmp = map;
	i = 0;
	k = -1;
	while (tmp)
	{
		j = -1;
		while (((char *)tmp->content)[++j])
		{
			if (((char *)tmp->content)[j] == 'D')
			{
				(*door)[++k].x = j;
				(*door)[k].y = i;
				(*door)[k].is_open = false;
			}
		}
		i++;
		tmp = tmp->next;
	}
}

void	load_textures(t_texture *texture, void *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		texture[i].img = mem_alloc(sizeof(t_img));
		texture[i].img->img = mlx_xpm_file_to_image(mlx, texture[i].path,
				&texture[i].width, &texture[i].height);
		if (!texture[i].img->img)
			error_exit("Invalid texture");
		texture[i].img->addr = mlx_get_data_addr(texture[i].img->img,
				&texture[i].img->bits_per_pixel, &texture[i].img->line_length,
				&texture[i].img->endian);
	}
}
