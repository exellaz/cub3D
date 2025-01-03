/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:17:49 by we                #+#    #+#             */
/*   Updated: 2024/12/23 22:17:47 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>

# include <mlx.h>
# include <Libft.h>

# include "graphics.h"

int		validate_arg(int argc, char *file);
void	setup_mlx(t_mlx *m);

#endif
