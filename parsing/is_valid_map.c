/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:19:34 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:24:53 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_available_block2(char **two_d_map, int p_count)
{
	int	i;
	int	j;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		j = 0;
		while (two_d_map[i][j] != '\0')
		{
			if (two_d_map[i][j] == 'N' || two_d_map[i][j] == 'S' 
				|| two_d_map[i][j] == 'E' || two_d_map[i][j] == 'W')
				p_count++;
			j++;
		}
		i++;
	}
	if (p_count == 1)
		return (1);
	return (0);
}

int	is_available(char **two_d_map)
{
	int		p_count;

	p_count = 0;
	return (is_available_block2(two_d_map, p_count));
}

int	is_valid(char **two_d_map)
{
	int	i;
	int	j;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		j = 0;
		while (two_d_map[i][j] != '\0')
		{
			if (two_d_map[i][j] != '1' && two_d_map[i][j] != '0' && 
			two_d_map[i][j] != ' ' && two_d_map[i][j] != 'N' && 
			two_d_map[i][j] != 'S' && two_d_map[i][j] != 'E' && 
			two_d_map[i][j] != 'W')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_reach(t_parsing_map_cp *map_cp, int row, int col)
{
	if (map_cp->map_cp[row] == NULL)
		return (1);
	if (map_cp->map_cp[row][col] == '1' || map_cp->map_cp[row][col] == 'F')
		return (0);
	else if (map_cp->map_cp[row][col] == ' ' 
	|| map_cp->map_cp[row][col] == '\0' || row == 0 || col == 0)
		return (1);
	else
		map_cp->map_cp[row][col] = 'F';
	if (map_cp->num_of_elements_in_each_row[row + 1] < col 
		|| map_cp->num_of_elements_in_each_row[row - 1] < col)
		return (1);
	return (is_reach(map_cp, row + 1, col) | is_reach(map_cp, row - 1, col) 
		| is_reach(map_cp, row, col + 1) | is_reach(map_cp, row, col - 1));
}

int	is_reachable(char **two_d_map)
{
	t_parsing_map_cp	*map_cp;
	int					row;
	int					col;
	int					res;

	map_cp = map_copy(two_d_map);
	if (map_cp == NULL)
	{
		free_list_str(two_d_map);
		exit(1);
	}
	row = 0;
	col = 0;
	index_player(map_cp->map_cp, &row, &col);
	res = is_reach(map_cp, row, col);
	free_list_str(map_cp->map_cp);
	free(map_cp->num_of_elements_in_each_row);
	free(map_cp);
	return (res);
}
