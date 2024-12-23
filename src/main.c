/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:31:54 by we                #+#    #+#             */
/*   Updated: 2024/12/23 22:48:34 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"
# include "map.h"

void	print(void *content);

int	main(int argc, char *argv[])
{
	t_list	*raw;
	int		fd;

	fd = validate_arg(argc, argv[1]);
	raw = load_file(fd);
	ft_lstiter(raw, &print);
	ft_lstclear(&raw, &free);

	return (0);
}

void	print(void *content)
{
	ft_printf("%s", (char *)content);
}
