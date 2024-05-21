/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:39:49 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:40:13 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_rgb_and_conv(t_parsing *parsing)
{
	if (parsing->r[0] < 0 || parsing->r[0] > 255 || 
		parsing->r[1] < 0 || parsing->r[1] > 255 || 
		parsing->g[0] < 0 || parsing->g[0] > 255 || 
		parsing->g[1] < 0 || parsing->g[1] > 255 || 
		parsing->b[0] < 0 || parsing->b[0] > 255 || 
		parsing->b[1] < 0 || parsing->b[1] > 255)
		return (1);
	parsing->rgb[0] = (parsing->r[0] << 16) + 
		(parsing->g[0] << 8) + parsing->b[0];
	parsing->rgb[1] = (parsing->r[1] << 16) + 
		(parsing->g[1] << 8) + parsing->b[1];
	return (0);
}

void	free_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (map->textures[i] != NULL)
			mlx_destroy_image(map->mlx_ptr, map->textures[i]);
		i++;
	}
}

void	assign_null_to_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		map->textures[i] = NULL;
		i++;
	}
}

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nThere is no file with this name\n", 38);
		exit (1);
	}
	return (fd);
}
