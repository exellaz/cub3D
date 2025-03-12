/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:23:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/03/12 11:02:47 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include "defines.h"

char	**lst_to_arr(t_list *lst);
t_list	*skip_empty_lines(t_list *raw);
bool	is_whitespace(char c);
bool	is_num(char *str);
void	print_arr(char **arr);
int		count_arr(char **arr);
void	free_img(t_img *img, void *mlx);
void	put_pixel(int x, int y, int color, t_img *img);
int		apply_opacity(int color, int opacity_int);

#endif
