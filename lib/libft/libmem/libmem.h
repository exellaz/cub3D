/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:51:40 by we                #+#    #+#             */
/*   Updated: 2025/03/13 14:14:16 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMEM_H
# define LIBMEM_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_mem
{
	int				id;
	void			*address;
	bool			isfreed;
	struct s_mem	*next;
}	t_mem;

t_mem	*mem_init(void);
void	*mem_alloc(size_t size);
void	mem_free(void *ptr);
void	mem_free_arr(void *ptr);
void	mem_clean(void);
void	mem_debug(void);

#endif
