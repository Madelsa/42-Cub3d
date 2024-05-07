/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:11 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/07 13:04:06 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	ray_inits(t_map *map, double rayAngle, int i)
{
	map->player->ray[i]->is_facing_up = rayAngle > 0 && rayAngle < PI;
	map->player->ray[i]->is_facing_down = !map->player->ray[i]->is_facing_up;
	map->player->ray[i]->is_facing_left = rayAngle > PI / 2 && rayAngle < (3
			* PI) / 2;
	map->player->ray[i]->is_facing_right = !map->player->ray[i]->is_facing_left;
	map->player->ray[i]->vert_wall_hit_x = 0;
	map->player->ray[i]->vert_wall_hit_y = 0;
	map->player->ray[i]->horz_wall_hit_x = 0;
	map->player->ray[i]->horz_wall_hit_y = 0;
	map->player->ray[i]->found_horz_wall_hit = 0;
	map->player->ray[i]->found_vert_wall_hit = 0;
	map->player->ray[i]->is_north_wall = 0;
	map->player->ray[i]->is_south_wall = 0;
	map->player->ray[i]->is_east_wall = 0;
	map->player->ray[i]->is_west_wall = 0;
}

void	cast_ray(t_map *map, double rayAngle, int i)
{
	normalize_angle(&rayAngle);
	ray_inits(map, rayAngle, i);
	find_horz_intercept(map, rayAngle, i);
	find_vert_intercept(map, rayAngle, i);
	calculate_distance(map, rayAngle, i);
}

void	wall_hit_direction(t_map *map, int i)
{
	if (map->player->ray[i]->is_facing_up
		&& map->player->ray[i]->was_hit_vertical == 0)
		map->player->ray[i]->is_north_wall = 1;
	else if (map->player->ray[i]->is_facing_down
		&& map->player->ray[i]->was_hit_vertical == 0)
		map->player->ray[i]->is_south_wall = 1;
	else if (map->player->ray[i]->is_facing_right
		&& map->player->ray[i]->was_hit_vertical == 1)
		map->player->ray[i]->is_east_wall = 1;
	else if (map->player->ray[i]->is_facing_left
		&& map->player->ray[i]->was_hit_vertical == 1)
		map->player->ray[i]->is_west_wall = 1;
}

void	choose_intercept(t_map *map, double vertHitDistance,
		double horzHitDistance, int i)
{
	if (vertHitDistance < horzHitDistance)
	{
		map->player->ray[i]->distance = vertHitDistance;
		map->player->ray[i]->wall_hit_x = map->player->ray[i]->vert_wall_hit_x;
		map->player->ray[i]->wall_hit_y = map->player->ray[i]->vert_wall_hit_y;
		map->player->ray[i]->was_hit_vertical = 1;
	}
	else
	{
		map->player->ray[i]->distance = horzHitDistance;
		map->player->ray[i]->wall_hit_x = map->player->ray[i]->horz_wall_hit_x;
		map->player->ray[i]->wall_hit_y = map->player->ray[i]->horz_wall_hit_y;
		map->player->ray[i]->was_hit_vertical = 0;
	}
}

void	cast_all_rays(t_map *map)
{
	double	ray_angle;
	int		i;

	ray_angle = map->player->rotation_angle + (FOV / 2);
	map->window_width = map->map_width * TWO_D_TILE_SIZE;
	map->window_height = map->map_height * TWO_D_TILE_SIZE;
	i = 0;
	while (i < map->no_of_rays)
	{
		cast_ray(map, ray_angle, i);
		ray_angle -= FOV / map->no_of_rays ;
		i++;
	}
}
