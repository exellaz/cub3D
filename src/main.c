/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:31:54 by we                #+#    #+#             */
/*   Updated: 2024/12/26 15:17:19 by we               ###   ########.fr       */
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

	return (0);
}

void	print(void *content)
{
	ft_printf("%s", (char *)content);
}
