/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:31:54 by we                #+#    #+#             */
/*   Updated: 2025/01/03 10:45:33 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"
# include "map.h"

void	print(void *content);

int	main(int argc, char *argv[])
{
	t_map	*map;
	int		file;

	file = validate_arg(argc, argv[1]);
	map = parse_map(file);
	for (int i = 0; i < 4; i++)
		printf("%s", map->texture_path[i]);
	printf("\n");
	printf("%d %d %d\n", map->ceiling_rgb[0], map->ceiling_rgb[1], map->ceiling_rgb[2]);
	printf("%d %d %d\n", map->floor_rgb[0], map->floor_rgb[1], map->floor_rgb[2]);
	ft_lstiter(map->map, print);
	mem_clean();

	return (0);
}

void	print(void *content)
{
	printf("%s", (char *)content);
}
