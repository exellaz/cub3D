/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:56:29 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/07 21:56:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Libft.h>
#include <mlx.h>

#include "graphics.h"
#include "map.h"
#include "utils.h"

int	count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_img(t_img *img, void *mlx)
{
	mlx_destroy_image(mlx, img->img);
	mem_free(img);
}
