/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_modifications.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:39:31 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 16:36:34 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_rotation_direction(t_map *map, int i, int j)
{
	if (map->map_mod[i][j] == 'N' || map->map_mod[i][j] == 'S'
		|| map->map_mod[i][j] == 'E' ||
		map->map_mod[i][j] == 'W')
	{
		map->player->x = j;
		map->player->y = i;
		if (map->map_mod[i][j] == 'S')
			map->player->rotation_angle = (3 * M_PI) / 2;
		else if (map->map_mod[i][j] == 'E')
			map->player->rotation_angle = 0;
		else if (map->map_mod[i][j] == 'W')
			map->player->rotation_angle = M_PI;
		map->map_mod[i][j] = '0';
	}
}

void	replace_chars(t_map *map, int longest_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_height)
	{
		j = 0;
		while (j < longest_line)
		{
			if (map->map_mod[i][j] != 'N' && map->map_mod[i][j] != 'S'
				&& map->map_mod[i][j] != 'E' &&
				map->map_mod[i][j] != 'W' && map->map_mod[i][j] != '0'
					&& map->map_mod[i][j] != '1')
				map->map_mod[i][j] = '1';
			set_rotation_direction(map, i, j);
			j++;
		}
		map->map_mod[i][longest_line] = '\0';
		i++;
	}
	map->map_height -= 1;
}

void	allocate_map_mod(t_map *map, int longest_line)
{
	int	i;

	map->map_mod = malloc(sizeof(char **) * (map->map_height + 1));
	i = 0;
	while (i < map->map_height)
	{
		map->map_mod[i] = malloc(sizeof(char *) * (longest_line + 1));
		ft_strcpy(map->map_mod[i], map->map[i]);
		i++;
	}
	map->map_mod[i] = NULL;
}

int	find_longest_line_length(t_map *map)
{
	int	max_length;
	int	i;
	int	length;

	max_length = 0;
	i = 0;
	while (map->map[i] != NULL)
	{
		length = ft_strlen(map->map[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	map->map_height = i;
	map->map_width = max_length;
	return (max_length);
}
