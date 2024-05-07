/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:23:40 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/07 12:55:23 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			map->player->ray[i]->found_horz_wall_hit = 1;
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
			map->player->ray[i]->found_vert_wall_hit = 1;
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

	map->player->ray[i]->yint = floor(map->player->y / TWO_D_TILE_SIZE) * TWO_D_TILE_SIZE;
	if (map->player->ray[i]->is_facing_down)
		map->player->ray[i]->yint += TWO_D_TILE_SIZE;
	// Find the x-coordinate of the closest horizontal grid intersection
	map->player->ray[i]->xint = map->player->x + (map->player->ray[i]->yint
			- map->player->y) / tan(-rayAngle); // Invert rotation here
	// Calculate the increment xstep and ystep
	map->player->ray[i]->ystep = TWO_D_TILE_SIZE;
	if (map->player->ray[i]->is_facing_up)
		map->player->ray[i]->ystep *= -1;
	map->player->ray[i]->xstep = TWO_D_TILE_SIZE / tan(-rayAngle);
	// Invert rotation here
	if (map->player->ray[i]->is_facing_left && map->player->ray[i]->xstep > 0)
		map->player->ray[i]->xstep *= -1;
	if (map->player->ray[i]->is_facing_right && map->player->ray[i]->xstep < 0)
		map->player->ray[i]->xstep *= -1;
	next_horz_touch_x = map->player->ray[i]->xint;
	next_horz_touch_y = map->player->ray[i]->yint;
	horizontal_intercept_loop(map, i, next_horz_touch_x, next_horz_touch_y);
}

void	find_vert_intercept(t_map *map, double rayAngle, int i)
{
	double	next_vert_touch_x;
	double	next_vert_touch_y;

	// Find the x-coordinate of the closest vertical grid intersection
	map->player->ray[i]->xint = floor(map->player->x / TWO_D_TILE_SIZE) * TWO_D_TILE_SIZE;
	if (map->player->ray[i]->is_facing_right)
		map->player->ray[i]->xint += TWO_D_TILE_SIZE;
	// Find the y-coordinate of the closest vertical grid intersection
	map->player->ray[i]->yint = map->player->y + (map->player->ray[i]->xint
			- map->player->x) * tan(-rayAngle); // Invert rotation here
	// Calculate the increment map->player->ray[i]->xstep and map->player->ray[i]->ystep
	map->player->ray[i]->xstep = TWO_D_TILE_SIZE;
	if (map->player->ray[i]->is_facing_left)
		map->player->ray[i]->xstep *= -1;
	map->player->ray[i]->ystep = TWO_D_TILE_SIZE * tan(-rayAngle);
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


void	calculate_distance(t_map *map, double rayAngle, int i)
{
	double	horz_hit_distance;
	double	vert_hit_distance;

	horz_hit_distance = INT_MAX;
	vert_hit_distance = INT_MAX;
	if (map->player->ray[i]->found_horz_wall_hit)
	{
		horz_hit_distance = distance_between_points(map,
				map->player->ray[i]->horz_wall_hit_x,
				map->player->ray[i]->horz_wall_hit_y);
	}
	if (map->player->ray[i]->found_vert_wall_hit)
	{
		vert_hit_distance = distance_between_points(map,
				map->player->ray[i]->vert_wall_hit_x,
				map->player->ray[i]->vert_wall_hit_y);
	}
	choose_intercept(map, vert_hit_distance, horz_hit_distance, i);
	map->player->ray[i]->ray_angle = rayAngle;
	wall_hit_direction(map, i);
}
