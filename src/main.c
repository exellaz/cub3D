/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:20:41 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/12 09:56:31 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	draw_loop(t_vars *vars);

int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = validate_arg(ac, av[1]);
	init_vars(&vars, fd);
	mlx_loop_hook(vars.mlx, &draw_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

static int	draw_loop(t_vars *vars)
{
	t_player	*player;

	player = vars->player;
	frame_counter(vars->fps);
	handle_player_controls(player, vars->fps, vars->map_data, vars);
	update_doors(vars->map_data);
	raycast(vars);
	if (vars->minimap_toggle == true)
		render_minimap(player, vars, vars->map_data);
	if (player->torch_toggle == true)
		render_sprite(vars, vars->sprite);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
