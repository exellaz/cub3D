// FILE: src/test_main.c

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "Libft.h"

void test_ft_split(void)
{
	char **arr = ft_split("hello world", ' ');
	assert(arr != NULL);
	assert(strcmp(arr[0], "hello") == 0);
	assert(strcmp(arr[1], "world") == 0);
	assert(arr[2] == NULL);
	mem_free(arr);
}

void test_get_next_line(void)
{
	int fd = open("Makefile", O_RDONLY);
	assert(fd != -1);
	char *line = get_next_line(fd);
	assert(line != NULL);
	printf("%s\n", line); // Optional: Print the line for visual verification
	mem_free(line);
	close(fd);
}

void test_ft_substr(void)
{
	char *str = ft_substr("hello world", 6, 5);
	assert(str != NULL);
	assert(strcmp(str, "world") == 0);
	mem_free(str);
}

void test_lst(void)
{
	t_list *lst = ft_lstnew("hello");
	assert(lst != NULL);
	ft_lstadd_front(&lst, ft_lstnew("world"));
	ft_lstadd_back(&lst, ft_lstnew("42"));

	t_list *node = lst;
	assert(strcmp((char *)node->content, "world") == 0);
	node = node->next;
	assert(strcmp((char *)node->content, "hello") == 0);
	node = node->next;
	assert(strcmp((char *)node->content, "42") == 0);
	node = node->next;
	assert(node == NULL);

	// Clean up
	ft_lstclear(&lst, mem_free);
}

int main(void)
{
	test_ft_split();
	test_get_next_line();
	test_ft_substr();
	test_lst();
	mem_clean();
	printf("All tests passed!\n");
	return 0;
}
