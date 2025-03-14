/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:55:33 by we                #+#    #+#             */
/*   Updated: 2025/03/14 09:21:01 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// validates argc and file
// if valid, opens the file and returns the file descriptor
// if invalid, prints an error message and exits the program
int	validate_arg(int argc, char *file)
{
	int		fd;
	bool	is_valid;

	is_valid = false;
	if (argc != 2 || !file)
		ft_putstr_fd("Error: Usage: ./cub3D <map.cub>\n", STDERR_FILENO);
	else if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
		ft_putstr_fd("Error: Invalid file extension\n", STDERR_FILENO);
	else
	{
		fd = open(file, O_RDONLY);
		is_valid = fd != -1;
		if (!is_valid)
			perror("ErroR");
	}
	if (!is_valid)
		// printf("is_valid: %d\n", is_valid);
		exit(EXIT_FAILURE);
	return (fd);
}
