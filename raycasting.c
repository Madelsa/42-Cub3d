/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:23:40 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/30 15:47:38 by mabdelsa         ###   ########.fr       */
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

void	horizontal_intercept_loop(t_map *map, int i, double next_horz_touch_x,
		double next_horz_touch_y)
{
	double	x_check;
	double	y_check;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= map->window_width
		&& next_horz_touch_y >= 0 && next_horz_touch_y <= map->window_height)
	{
		x_check = next_horz_touch_x;
		y_check = next_horz_touch_y;
		if (map->player->ray[i]->is_facing_up)
			y_check -= 1;
		if (check_wall_index(map, x_check, y_check))
		{
			// found a wall hit
			map->player->ray[i]->horz_wall_hit_x = next_horz_touch_x;
			map->player->ray[i]->horz_wall_hit_y = next_horz_touch_y;
			map->player->ray[i]->found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			next_horz_touch_x += map->player->ray[i]->xstep;
			next_horz_touch_y += map->player->ray[i]->ystep;
		}
	}
}

void	vertical_intercept_loop(t_map *map, int i, double next_vert_touch_x,
		double next_vert_touch_y)
{
	double	x_check;
	double	y_check;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= map->window_width
		&& next_vert_touch_y >= 0 && next_vert_touch_y <= map->window_height)
	{
		x_check = next_vert_touch_x;
		y_check = next_vert_touch_y;
		if (map->player->ray[i]->is_facing_left)
			x_check -= 1;
		if (check_wall_index(map, x_check, y_check))
		{
			// found a wall hit
			map->player->ray[i]->vert_wall_hit_x = next_vert_touch_x;
			map->player->ray[i]->vert_wall_hit_y = next_vert_touch_y;
			map->player->ray[i]->found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			next_vert_touch_x += map->player->ray[i]->xstep;
			next_vert_touch_y += map->player->ray[i]->ystep;
		}
	}
}

void	find_horz_intercept(t_map *map, double rayAngle, int i)
{
	double	next_horz_touch_x;
	double	next_horz_touch_y;

	// Find the y-coordinate of the closest horizontal grid intersection
	map->player->ray[i]->yint = floor(map->player->y / TILE_SIZE) * TILE_SIZE;
	if (map->player->ray[i]->is_facing_down)
		map->player->ray[i]->yint += TILE_SIZE;
	// Find the x-coordinate of the closest horizontal grid intersection
	map->player->ray[i]->xint = map->player->x + (map->player->ray[i]->yint
			- map->player->y) / tan(-rayAngle); // Invert rotation here
	// Calculate the increment map->player->ray[i]->xstep and map->player->ray[i]->ystep
	map->player->ray[i]->ystep = TILE_SIZE;
	if (map->player->ray[i]->is_facing_up)
		map->player->ray[i]->ystep *= -1;
	map->player->ray[i]->xstep = TILE_SIZE / tan(-rayAngle);
	// Invert rotation here
	if ((map->player->ray[i]->is_facing_left && map->player->ray[i]->xstep > 0)
		|| (map->player->ray[i]->is_facing_right
			&& map->player->ray[i]->xstep < 0))
		map->player->ray[i]->xstep *= -1;
	next_horz_touch_x = map->player->ray[i]->xint;
	next_horz_touch_y = map->player->ray[i]->yint;
	// Increment map->player->ray[i]->xstep and map->player->ray[i]->ystep until we find a wall
	horizontal_intercept_loop(map, i, next_horz_touch_x, next_horz_touch_y);
}

void	find_vertical_intercept(t_map *map, double rayAngle, int i)
{
	double	next_vert_touch_x;
	double	next_vert_touch_y;

	// Find the x-coordinate of the closest vertical grid intersection
	map->player->ray[i]->xint = floor(map->player->x / TILE_SIZE) * TILE_SIZE;
	if (map->player->ray[i]->is_facing_right)
		map->player->ray[i]->xint += TILE_SIZE;
	// Find the y-coordinate of the closest vertical grid intersection
	map->player->ray[i]->yint = map->player->y + (map->player->ray[i]->xint
			- map->player->x) * tan(-rayAngle); // Invert rotation here
	// Calculate the increment map->player->ray[i]->xstep and map->player->ray[i]->ystep
	map->player->ray[i]->xstep = TILE_SIZE;
	if (map->player->ray[i]->is_facing_left)
		map->player->ray[i]->xstep *= -1;
	map->player->ray[i]->ystep = TILE_SIZE * tan(-rayAngle);
	// Invert rotation here
	if ((map->player->ray[i]->is_facing_up && map->player->ray[i]->ystep > 0)
		|| (map->player->ray[i]->is_facing_down
			&& map->player->ray[i]->ystep < 0))
		map->player->ray[i]->ystep *= -1;
	next_vert_touch_x = map->player->ray[i]->xint;
	next_vert_touch_y = map->player->ray[i]->yint;
	// Increment map->player->ray[i]->xstep and map->player->ray[i]->ystep until we find a wall
	vertical_intercept_loop(map, i, next_vert_touch_x, next_vert_touch_y);
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

void	calculate_distance(t_map *map, double rayAngle, int i)
{
	double	horz_hit_distance;
	double	vert_hit_distance;

	horz_hit_distance = distance_between_points(map,
			map->player->ray[i]->horz_wall_hit_x,
			map->player->ray[i]->horz_wall_hit_y);
	vert_hit_distance = distance_between_points(map,
			map->player->ray[i]->vert_wall_hit_x,
			map->player->ray[i]->vert_wall_hit_y);
	if (vert_hit_distance < horz_hit_distance)
	{
		map->player->ray[i]->distance = vert_hit_distance;
		map->player->ray[i]->wall_hit_x = map->player->ray[i]->vert_wall_hit_x;
		map->player->ray[i]->wall_hit_y = map->player->ray[i]->vert_wall_hit_y;
		map->player->ray[i]->was_hit_vertical = 1;
	}
	else
	{
		map->player->ray[i]->distance = horz_hit_distance;
		map->player->ray[i]->wall_hit_x = map->player->ray[i]->horz_wall_hit_x;
		map->player->ray[i]->wall_hit_y = map->player->ray[i]->horz_wall_hit_y;
		map->player->ray[i]->was_hit_vertical = 0;
	}
	map->player->ray[i]->ray_angle = rayAngle;
	wall_hit_direction(map, i);
}

void	cast_ray(t_map *map, double rayAngle, int i)
{
	normalize_angle(&rayAngle);
	ray_inits(map, rayAngle, i);
	find_horz_intercept(map, rayAngle, i);
	find_vertical_intercept(map, rayAngle, i);
	calculate_distance(map, rayAngle, i);
}

void	cast_all_rays(t_map *map)
{
	double	ray_angle;
	int		i;

	ray_angle = map->player->rotation_angle - (FOV / 2);
	map->window_width = map->map_width * TILE_SIZE;
	map->window_height = map->map_height * TILE_SIZE;
	i = 0;
	while (i < map->no_of_rays)
	{
		cast_ray(map, ray_angle, i);
		printf("Ray ID: %d Wall Hit: %d %d% d% d\n", i,
				map->player->ray[i]->is_north_wall,
				map->player->ray[i]->is_south_wall,
				map->player->ray[i]->is_east_wall,
				map->player->ray[i]->is_west_wall);
		ray_angle += FOV / map->no_of_rays;
		i++;
	}
}
