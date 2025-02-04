/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:07:45 by we                #+#    #+#             */
/*   Updated: 2025/01/15 14:00:53 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef struct s_vars	t_vars;

int		quit(int keycode, t_vars *mlx);
int		key_press_hook(int keycode, t_vars *mlx);
int		key_release_hook(int keycode, t_vars *mlx);

# endif
