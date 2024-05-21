/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:28:07 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 20:19:22 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	building_map_block2(t_linked_list_map **linked_list_map, 
t_linked_list_map *new_row, t_linked_list_map **last_row, int i)
{
	if (i == 0)
	{
		*linked_list_map = new_row;
		*last_row = new_row;
	}
	else
	{
		(*last_row)->next = new_row;
		*last_row = (*last_row)->next;
	}
}

t_linked_list_map	*building_map(t_linked_list_map *linked_list_map, int fd)
{
	t_linked_list_map	*new_row;
	t_linked_list_map	*last_row;
	char				*temp_str;
	int					i;

	temp_str = get_next_line(fd);
	if (temp_str == NULL)
		empty_map(fd);
	i = 0;
	while (temp_str != NULL)
	{
		new_row = malloc(sizeof(t_linked_list_map));
		if (new_row == NULL)
		{
			free_map(linked_list_map);
			exit(1);
		}
		building_map_block2(&linked_list_map, new_row, &last_row, i);
		last_row->row = temp_str;
		last_row->next = NULL;
		temp_str = get_next_line(fd);
		i++;
	}
	return (linked_list_map);
}

t_linked_list_map	*trim_map(t_linked_list_map *linked_list_map)
{
	t_linked_list_map	*temp_map;

	temp_map = linked_list_map;
	while (temp_map != NULL)
	{
		if (temp_map->row[ft_strlen(temp_map->row) - 1] == '\n')
			temp_map->row[ft_strlen(temp_map->row) - 1] = '\0';
		temp_map = temp_map->next;
	}
	return (linked_list_map);
}

void	conv_tow_d_map_block2(t_linked_list_map *temp_map2, 
char **two_d_map, int i, t_linked_list_map *map)
{
	int		j;

	i = 0;
	while (temp_map2 != NULL)
	{
		two_d_map[i] = malloc(ft_strlen(temp_map2->row) + 1);
		if (two_d_map[i] == NULL)
		{
			free_list_str(two_d_map);
			free_map(map);
			exit(0);
		}
		j = 0;
		while (temp_map2->row[j] != '\0')
		{
			two_d_map[i][j] = temp_map2->row[j];
			j++;
		}
		two_d_map[i][j] = '\0';
		temp_map2 = temp_map2->next;
		i++;
	}
	two_d_map[i] = NULL;
}

char	**conv_two_d_map(t_linked_list_map *map, char **two_d_map, 
	int main_map_row_num)
{
	t_linked_list_map	*temp_map;
	t_linked_list_map	*temp_map2;
	int					i;

	temp_map = map;
	i = -1;
	while (++i < main_map_row_num)
		temp_map = temp_map->next;
	temp_map2 = temp_map;
	i = 0;
	while (temp_map != NULL)
	{
		temp_map = temp_map->next;
		i++;
	}
	two_d_map = malloc((i + 1) * sizeof(char *));
	if (two_d_map == NULL)
	{
		free_map(map);
		exit(1);
	}
	i = 0;
	conv_tow_d_map_block2(temp_map2, two_d_map, i, map);
	return (two_d_map);
}
