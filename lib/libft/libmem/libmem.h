/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:51:40 by we                #+#    #+#             */
/*   Updated: 2024/12/31 13:47:50 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMEM_H
# define LIBMEM_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# ifndef DEBUG
#  define DEBUG printf
# endif

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
