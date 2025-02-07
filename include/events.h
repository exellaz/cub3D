/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:07:45 by we                #+#    #+#             */
/*   Updated: 2025/02/07 11:09:09 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <X11/keysym.h>
# include "defines.h"

typedef struct s_vars	t_vars;

int		quit(int keycode, t_vars *mlx);
int		key_press_hook(int keycode, t_vars *mlx);
int		key_release_hook(int keycode, t_vars *mlx);

# endif
