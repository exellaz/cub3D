/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:33:35 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/01/17 13:30:09 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	frame_counter(t_fps *fps)
{
	fps->frame_count++;

	clock_t	current_time = clock();
	float	elapsed_time = (float)(current_time - fps->start_time) / CLOCKS_PER_SEC;

	fps->frame_time = (float)(current_time - fps->last_frame_time) / CLOCKS_PER_SEC;
	fps->last_frame_time = current_time;

	if (elapsed_time >= 1.0)
	{
		fps->fps = fps->frame_count / elapsed_time;
		printf("FPS: %.2f\n", fps->fps);
		fps->frame_count = 0;
		fps->start_time = current_time;
	}
	return (0);
}