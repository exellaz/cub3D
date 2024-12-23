# include "cub3D.h"

int	main(int argc, char *argv[])
{
	int	fd;

	fd = validate_arg(argc, argv[1]);
	ft_printf("File descriptor: %d\n", fd);
	
	return (0);
}
