/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:23:14 by we                #+#    #+#             */
/*   Updated: 2024/12/31 14:23:18 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmem.h"

// initialze the block once
// subsequent calls will return the same block
t_mem	*mem_init(void)
{
	static t_mem	*block;

	if (!block)
	{
		block = malloc(sizeof(t_mem));
		if (!block)
			return (NULL);
		block->id = 0;
		block->address = NULL;
		block->isfreed = false;
		block->next = NULL;
	}
	return (block);
}

// use like malloc()
void	*mem_alloc(size_t size)
{
	t_mem	*block;

	block = mem_init();
	while (block->next)
		block = block->next;
	block->next = malloc(sizeof(t_mem));
	if (!block->next)
		return (NULL);
	block->next->id = block->id + 1;
	block = block->next;
	block->address = malloc(size);
	if (!block->address)
		return (NULL);
	block->isfreed = false;
	block->next = NULL;
	return (block->address);
}

// use with `mem_alloc()`, will not double free
void	mem_free(void *ptr)
{
	t_mem	*block;

	block = mem_init();
	while (block)
	{
		if (block->address == ptr)
		{
			free(block->address);
			block->address = NULL;
			block->isfreed = true;
			break ;
		}
		if (!block->next)
			break ;
		block = block->next;
	}
}

// use at the end of the program or when encouter error
void	mem_clean(void)
{
	t_mem	*block;
	t_mem	*tmp;

	block = mem_init();
	while (block)
	{
		if (!block->isfreed)
			free(block->address);
		block->address = NULL;
		tmp = block->next;
		free(block);
		block = tmp;
	}
}

void	mem_debug(void)
{
	t_mem	*block;

	block = mem_init();
	while (block)
	{
		DEBUG("block->id: %d\n", block->id);
		DEBUG("block->address: %p\n", block->address);
		DEBUG("block->isfreed: %d\n", block->isfreed);
		DEBUG("block->next: %p\n", (void *)block->next);
		block = block->next;
	}
}
