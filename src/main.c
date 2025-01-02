# include "Libft.h"

int	main(void)
{
	// test split
	{
		char	**arr;
		int		i;

		arr = ft_split("hello world", ' ');
		i = 0;
		while (arr[i])
		{
			printf("%s\n", arr[i]);
			i++;
		}
		mem_free(arr);
	}
	// test get_next_line
	{
		int		fd;
		char	*line;

		fd = open("Makefile", O_RDONLY);
		while ((line = get_next_line(fd)))
			printf("%s\n", line);
		mem_free(line);
		close(fd);
	}
	mem_clean();
	return (0);
}
