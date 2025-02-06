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
