/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:49:28 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/22 14:38:20 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_values(t_map *map)
{
	int	i;

	map->img_height = 10;
	map->img_width = 10;
	map->map_3d = malloc(sizeof(t_map_3d));
	map->player = malloc(sizeof(t_player));
	map->no_of_rays = WINDOW_WIDTH;
	map->player->ray = malloc(sizeof(t_ray *) * (map->no_of_rays + 1));
	i = 0;
	while (i < map->no_of_rays)
	{
		map->player->ray[i] = malloc(sizeof(t_ray));
		i++;
	}
	map->player->ray[i] = NULL;
	map->player->width = 3;
	map->player->height = 3;
	map->player->turn_direction = 0;
	map->player->walk_direction = 0;
	map->player->fov = 60 * (M_PI / 180);
	map->player->rotation_angle = M_PI / 2;
	map->player->walk_speed = 4;
	map->player->turn_speed = 15 * (M_PI / 180);
}

int	assign_images(t_map *map, t_parsing *parsing)
{
	map->rgb[0] = parsing->rgb[0];
	map->rgb[1] = parsing->rgb[1];
	map->img_height = 10;
	map->img_width = 10;
	map->textures[0] = mlx_xpm_file_to_image(map->mlx_ptr,
			"./textures_2/white_square_10.xpm", &map->img_width,
			&map->img_height);
	map->textures[1] = mlx_xpm_file_to_image(map->mlx_ptr,
			"./textures_2/black_square_10.xpm", &map->img_width,
			&map->img_height);
	if (map->textures[0] == NULL || map->textures[1] == NULL)
		return (1);
	return (0);
}

double	distance_between_points(t_map *map, double x2, double y2)
{
	return (sqrt((x2 - map->player->x) * (x2 - map->player->x) + (y2
				- map->player->y) * (y2 - map->player->y)));
}
