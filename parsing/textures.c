/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:34:09 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:37:42 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	read_wall_texture_block_2(int wall_direction, char **line, 
		t_parsing *parsing, t_map *map)
{
	if (line[1] != NULL && line[2] == NULL && wall_direction == 2 
		&& parsing->six_lines_done[2] == 0)
	{
		map->textures[4] = mlx_xpm_file_to_image(map->mlx_ptr, 
				line[1], &map->img_width, &map->img_height);
		if (map->textures[4] == NULL)
			return (write(1, "Error\nNo texture with this name\n", 32), 1);
		parsing->six_lines_done[2] = 1;
	}
	else if (line[1] != NULL && line[2] == NULL && wall_direction == 3 
		&& parsing->six_lines_done[3] == 0)
	{
		map->textures[5] = mlx_xpm_file_to_image(map->mlx_ptr, 
				line[1], &map->img_width, &map->img_height);
		if (map->textures[5] == NULL)
			return (write(1, "Error\nNo texture with this name\n", 41), 1);
		parsing->six_lines_done[3] = 1;
	}
	else
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}

int	read_wall_texture(int wall_direction, char **line, 
	t_parsing *parsing, t_map *map)
{
	if (line[1] != NULL && line[2] == NULL && wall_direction == 0 
		&& parsing->six_lines_done[0] == 0)
	{
		map->textures[2] = mlx_xpm_file_to_image(map->mlx_ptr, 
				line[1], &map->img_width, &map->img_height);
		if (map->textures[2] == NULL)
			return (write(1, "Error\nNo texture with this name\n", 32), 1);
		parsing->six_lines_done[0] = 1;
	}
	else if (line[1] != NULL && line[2] == NULL && wall_direction == 1 
		&& parsing->six_lines_done[1] == 0)
	{
		map->textures[3] = mlx_xpm_file_to_image(map->mlx_ptr, 
				line[1], &map->img_width, &map->img_height);
		if (map->textures[3] == NULL)
			return (write(1, "Error\nNo texture with this name\n", 32), 1);
		parsing->six_lines_done[1] = 1;
	}
	else
	{
		if (read_wall_texture_block_2(wall_direction, line, parsing, map) == 1)
			return (1);
	}
	return (0);
}

int	load_textures_and_colors3(char **line, t_parsing *parsing, t_map *map)
{
	if (line[0][0] == 'E' && line[0][1] == 'A' && line[0][2] == '\0')
	{
		if (read_wall_texture(2, line, parsing, map) == 1)
			return (free_double_pointer(line), 1);
	}
	else if (line[0][0] == 'W' && line[0][1] == 'E' && line[0][2] == '\0')
	{
		if (read_wall_texture(3, line, parsing, map) == 1)
			return (free_double_pointer(line), 1);
	}
	else if (line[0][0] == 'F' && line[0][1] == '\0')
	{
		if (save_colors(4, line, parsing) == 1)
			return (free_double_pointer(line), 1);
	}
	else if (line[0][0] == 'C' && line[0][1] == '\0')
	{
		if (save_colors(5, line, parsing) == 1)
			return (free_double_pointer(line), 1);
	}
	else
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}

int	load_textures_and_colors2(char **line, t_parsing *parsing, t_map *map)
{
	if (line[0] == NULL)
	{
		line[0] = NULL;
	}
	else if (line[0][0] == 'S' && line[0][1] == 'O' && line[0][2] == '\0')
	{
		if (read_wall_texture(0, line, parsing, map) == 1)
			return (free_double_pointer(line), 1);
	}
	else if (line[0][0] == 'N' && line[0][1] == 'O' && line[0][2] == '\0')
	{
		if (read_wall_texture(1, line, parsing, map) == 1)
			return (free_double_pointer(line), 1);
	}
	else if (load_textures_and_colors3(line, parsing, map) == 1)
		return (1);
	return (0);
}

int	load_textures_and_colors(t_linked_list_map	*linked_list_map, 
		t_parsing *parsing, t_map *map)
{
	t_linked_list_map	*temp_map;
	char				**line;

	six_lines_done_and_rgb_init(parsing);
	temp_map = linked_list_map;
	parsing->main_map_row_num = 0;
	while ((parsing->six_lines_done[0] == 0 || parsing->six_lines_done[1] == 0
			|| parsing->six_lines_done[2] == 0 
			|| parsing->six_lines_done[3] == 0
			|| parsing->six_lines_done[4] == 0 
			|| parsing->six_lines_done[5] == 0) && temp_map != NULL)
	{
		line = ft_split(temp_map->row, ' ');
		if (load_textures_and_colors2(line, parsing, map) == 1)
			return (1);
		temp_map = temp_map->next;
		parsing->main_map_row_num++;
		free_double_pointer(line);
	}
	if (temp_map == NULL)
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}
