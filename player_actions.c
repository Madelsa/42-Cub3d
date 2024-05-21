/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:43:45 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 16:43:23 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, M_PI * 2);
	if (*angle < 0)
		*angle += M_PI * 2;
}

void	rotate_line(t_map *map, double angle)
{
	map->player->turn_direction = angle;
	map->player->rotation_angle += map->player->turn_direction
		* map->player->turn_speed;
	normalize_angle(&map->player->rotation_angle);
}

int	check_wall_index(t_map *map, double x, double y)
{
	int	next_x;
	int	next_y;

	next_x = floor(x / TWO_D_TILE_SIZE);
	next_y = floor(y / TWO_D_TILE_SIZE);
	if (map->map[next_y][next_x] == '1')
		return (1);
	return (0);
}

void	move_player(t_map *map, int direction, int strafe)
{
	double	move_step;
	double	dx;
	double	dy;

	move_step = map->player->walk_speed;
	if (strafe == 0)
	{
		dx = cos(map->player->rotation_angle) * direction * move_step;
		dy = -sin(map->player->rotation_angle) * direction * move_step;
	}
	else
	{
		dx = cos(map->player->rotation_angle - (M_PI_2 * strafe)) * move_step;
		dy = -sin(map->player->rotation_angle - (M_PI_2 * strafe)) * move_step;
	}
	if (check_wall_index(map, map->player->x + dx * 1.1, map->player->y + dy
			* 1.1) == 0)
	{
		map->player->x += dx;
		map->player->y += dy;
	}
}

int	perform_action(int keycode, t_map *map)
{
	if (keycode == 53)
		destroy_window(map);
	else if (keycode == 123)
		rotate_line(map, 1);
	else if (keycode == 124)
		rotate_line(map, -1);
	else if (keycode == 13)
		move_player(map, 1, 0);
	else if (keycode == 1)
		move_player(map, -1, 0);
	else if (keycode == 0)
		move_player(map, 1, -1);
	else if (keycode == 2)
		move_player(map, 1, 1);
	map->player->walk_direction = 0;
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	draw_map(map);
	draw_player(map);
	draw_line(map);
	cast_all_rays(map);
	create_3d_walls(map);
	draw_map(map);
	draw_player(map);
	draw_line(map);
	return (0);
}
