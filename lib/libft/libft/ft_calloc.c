/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:44:10 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 13:02:02 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*ptr;
	size_t	total_size;

	if (element_size != 0 && num_elements > UINT_MAX / element_size)
		return (NULL);
	total_size = num_elements * element_size;
	if (num_elements != 0 && total_size / num_elements != element_size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr != NULL)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}

/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	int		*array;
	size_t	num_elements = 5;
	array = (int *)calloc(num_elements, sizeof(int));
	for (size_t i = 0; i < num_elements + 0; i++)
		array[i] = i * 10;
	for (size_t i = 0; i < num_elements + 0; i++)
		printf("array[%zu]: %d\n", i, array[i]);
	free(array);

	printf("\n");
	
	printf("ft_:\n");
	int		*array1;
	size_t	num_elements1 = 5;
	array1 = (int *)ft_calloc(num_elements1, sizeof(int));
	for (size_t i = 0; i < num_elements1 + 0; i++)
		array1[i] = i * 10;
	for (size_t i = 0; i < num_elements1 + 0; i++)
		printf("array[%zu]: %d\n", i, array1[i]);
	free(array1);
	
}
*/
