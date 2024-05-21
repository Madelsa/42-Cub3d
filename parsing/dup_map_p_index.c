/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_map_p_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:23:05 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 20:19:26 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	map_copy_block2(char **two_d_map, t_parsing_map_cp *map_cp, int j)
{
	int	i;

	j = 0;
	while (two_d_map[j] != NULL)
	{
		i = 0;
		map_cp->map_cp[j] = malloc(ft_strlen(two_d_map[j]) + 1);
		map_cp->num_of_elements_in_each_row[j] = ft_strlen(two_d_map[j]);
		if (map_cp->map_cp[j] == NULL)
		{
			free(map_cp->num_of_elements_in_each_row);
			free_list_str(two_d_map);
			free_list_str(map_cp->map_cp);
			free(map_cp);
			exit(1);
		}
		while (two_d_map[j][i] != '\0')
		{
			map_cp->map_cp[j][i] = two_d_map[j][i];
			i++;
		}
		map_cp->map_cp[j][i] = '\0';
		j++;
	}
	map_cp->map_cp[j] = NULL;
}

t_parsing_map_cp	*map_copy(char **two_d_map)
{
	t_parsing_map_cp	*map_cp;
	int					j;

	map_cp = malloc(sizeof(t_parsing_map_cp));
	if (map_cp == NULL)
	{
		free_list_str(two_d_map);
		exit(1);
	}
	j = 0;
	while (two_d_map[j] != NULL)
		j++;
	map_cp->map_cp = malloc((j + 1) * sizeof(char *));
	map_cp->num_of_elements_in_each_row = malloc(j * sizeof(int));
	if (map_cp->map_cp == NULL || map_cp->num_of_elements_in_each_row == NULL)
	{
		free_list_str(two_d_map);
		if (map_cp->map_cp != NULL)
			free(map_cp->map_cp);
		free(map_cp);
		if (map_cp->num_of_elements_in_each_row != NULL)
			free(map_cp->num_of_elements_in_each_row);
		exit(1);
	}
	return (map_copy_block2(two_d_map, map_cp, j), map_cp);
}

void	index_player(char **map_cp, int *row, int *col)
{
	*row = 0;
	while (map_cp[*row] != NULL)
	{
		*col = 0;
		while (map_cp[*row][*col] != '\0')
		{
			if (map_cp[*row][*col] == 'S' || map_cp[*row][*col] == 'N' || 
				map_cp[*row][*col] == 'E' || map_cp[*row][*col] == 'W')
				return ;
			(*col)++;
		}
		(*row)++;
	}
}
