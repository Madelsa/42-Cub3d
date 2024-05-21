/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:26:27 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:26:41 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	error(char **two_d_map)
{
	if (is_valid(two_d_map) == 0)
	{
		write(1, "Error\n", 6);
		write(1, "The map should have only 1, 0, N, S, E or W symbols\n", 52);
	}
	else if (is_available(two_d_map) == 0)
		write(1, "Error\nThe map should has 1 Player\n", 34);
	else if (is_reachable(two_d_map) == 1)
		write(1, "Error\nThe Player should be inside the walls\n", 44);
	else
		return ('Y');
	return ('N');
}

void	check_extension(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i >= 4 && file_name[i - 1] == 'b' && file_name[i - 2] == 'u' 
		&& file_name[i - 3] == 'c' && file_name[i - 4] == '.')
	{
		return ;
	}
	write(1, "Error\nWrong file extension\n", 27);
	exit(1);
}

void	empty_map(int fd)
{
	write(1, "Error\n", 6);
	write(1, "The map file is empty\n", 22);
	close(fd);
	exit(1);
}
