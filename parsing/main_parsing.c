/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:20:45 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:39:37 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_map(t_linked_list_map *a)
{
	t_linked_list_map	*c;

	c = a;
	while (a != NULL)
	{
		c = c->next;
		free(a->row);
		free(a);
		a = c;
	}
}

void	free_double_pointer(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	free_list_str(char	**two_d_map)
{
	int	i;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		free(two_d_map[i]);
		i++;
	}
	free(two_d_map);
}

void	parsing2(t_map *map, t_parsing *parsing, 
	t_linked_list_map *linked_list_map)
{
	map->map = NULL;
	map->map = conv_two_d_map(linked_list_map, map->map, 
			parsing->main_map_row_num);
	free_map(linked_list_map);
	if (error(map->map) == 'N')
	{
		free_list_str(map->map);
		free(parsing);
		free_textures(map);
		exit (1);
	}
	if (check_rgb_and_conv(parsing) == 1)
	{
		free_list_str(map->map);
		free(parsing);
		free_textures(map);
		exit (1);
	}
	if (assign_images(map, parsing) == 1)
	{
		free_list_str(map->map);
		free(parsing);
		free_textures(map);
		exit (1);
	}
}

void	parsing(char *file_name, t_map *map)
{
	int					fd;
	t_linked_list_map	*linked_list_map;
	t_parsing			*parsing;

	assign_null_to_textures(map);
	check_extension(file_name);
	fd = open_file(file_name);
	linked_list_map = NULL;
	linked_list_map = building_map(linked_list_map, fd);
	close(fd);
	linked_list_map = trim_map(linked_list_map);
	parsing = malloc(sizeof(t_parsing));
	if (parsing == NULL)
	{
		exit (1);
	}
	if (load_textures_and_colors(linked_list_map, parsing, map) == 1)
	{
		free_map(linked_list_map);
		free(parsing);
		free_textures(map);
		exit (1);
	}
	parsing2(map, parsing, linked_list_map);
	free(parsing);
}
