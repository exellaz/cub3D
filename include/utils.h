/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:23:13 by tjun-yu           #+#    #+#             */
/*   Updated: 2025/01/10 09:54:33 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_list	t_list;

char	**lst_to_arr(t_list *lst);
t_list	*skip_empty_lines(t_list *raw);
bool	is_num(char *str);

#endif
