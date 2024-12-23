/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:07:45 by we                #+#    #+#             */
/*   Updated: 2024/12/23 11:55:30 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef struct s_mlx	t_mlx;

int		quit(int keycode, t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);

# endif
