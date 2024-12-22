/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tanjunyu8888@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:24:06 by tjun-yu           #+#    #+#             */
/*   Updated: 2023/10/30 10:44:20 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	copy_len;
	int		i;

	if (dest == NULL && size == 0)
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	copy_len = size - dest_len - 1;
	i = -1;
	if (dest == 0)
		return (src_len);
	if (size <= dest_len)
		return (src_len + size);
	if (copy_len < src_len)
		while (++i < (int)copy_len)
			dest[dest_len + i] = src[i];
	else
		while (src[++i] != 0)
			dest[dest_len + i] = src[i];
	dest[dest_len + i] = 0;
	return (dest_len + src_len);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	printf("original:\n");
	char	dest[20] = "12345";
	char	src[] = "67890";
	printf("%zu: %s\n", strlcat(dest, src, 20), dest);
	char	dest2[20] = "12345";
	char	src2[] = "67890";
	printf("%zu: %s\n", strlcat(dest2, src2, 0), dest2);
	char	dest4[20] = "12345";
	char	src4[] = "67890";
	printf("%zu: %s\n", strlcat(dest4, src4, 10), dest4);
	char	dest6[20] = "";
	char	src6[] = "67890";
	printf("%zu: %s\n", strlcat(dest6, src6, 20), dest6);
	char	dest8[20] = "12345";
	char	src8[] = "67890";
	printf("%zu: %s\n", strlcat(dest8, src8, 4), dest8);
	char	src10[] = "67890";
	printf("%zu: %s\n", strlcat(dest8, src10, -1), dest8);

	printf("\n");

	printf("ft_:\n");
	char	dest1[20] = "12345";
	char	src1[] = "67890";
	printf("%zu: %s\n", ft_strlcat(dest1, src1, 20), dest1);
	char	dest3[20] = "12345";
	char	src3[] = "67890";
	printf("%zu: %s\n", ft_strlcat(dest3, src3, 0), dest3);
	char	dest5[20] = "12345";
	char	src5[] = "67890";
	printf("%zu: %s\n", ft_strlcat(dest5, src5, 10), dest5);
	char	dest7[20] = "";
	char	src7[] = "67890";
	printf("%zu: %s\n", ft_strlcat(dest7, src7, 20), dest7);
	char	dest9[20] = "12345";
	char	src9[] = "67890";
	printf("%zu: %s\n", ft_strlcat(dest9, src9, 4), dest9);
	char	src11[] = "67890";
	printf("%zu: %s\n", strlcat(dest8, src11, -1), dest8);
}
*/
