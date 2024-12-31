# include "libmem.h"

int	main(void)
{
	void	*ptr;
	void	*ptr1;
	void	*ptr2;

	ptr = mem_alloc(10);
	ptr = mem_alloc(20);
	ptr = mem_alloc(30);
	ptr1 = ptr;
	ptr2 = ptr1;
	mem_free(ptr);
	mem_debug();	printf("\n");
	mem_free(ptr1);
	mem_debug();	printf("\n");
	mem_free(ptr2);
	mem_debug();	printf("\n");
	mem_clean();
	return (0);
}
