/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem-1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:18:44 by kkhai-ki          #+#    #+#             */
/*   Updated: 2025/03/13 13:18:47 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmem.h"

// use for `ft_split()`
void	mem_free_arr(void *ptr)
{
	int	i;

	i = -1;
	while (((char **)ptr)[++i])
		mem_free(((char **)ptr)[i]);
	mem_free(ptr);
}
