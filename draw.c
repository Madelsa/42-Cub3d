/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:32:07 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 16:22:26 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y] != NULL)
	{
		x = 0;
		while (map->map[y][x] != '\0')
		{
			if (map->map[y][x] == '0')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->textures[0], (x * TWO_D_TILE_SIZE), (y
						* TWO_D_TILE_SIZE));
			else if (map->map[y][x] == '1')
				mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
					map->textures[1], (x * TWO_D_TILE_SIZE), (y
						* TWO_D_TILE_SIZE));
			x++;
		}
		y++;
	}
}

void	draw_player(t_map *map)
{
	int	draw_start_x;
	int	draw_start_y;
	int	x;
	int	y;

	draw_start_x = map->player->x - (map->player->width / 2);
	draw_start_y = map->player->y - (map->player->height / 2);
	x = draw_start_x;
	while (x < draw_start_x + map->player->width)
	{
		y = draw_start_y;
		while (y < draw_start_y + map->player->height)
		{
			mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	draw_line_2(t_map *map, int dx, int dy)
{
	int		steps;
	int		i;
	double	y;
	double	x;

	if (abs(dy) > abs(dx))
		steps = abs(dy);
	else
		steps = abs(dx);
	y = map->player->y;
	x = map->player->x;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, (int)x, (int)y, 0xFF0000);
		y += dy / (double)steps;
		x += dx / (double)steps;
		i++;
	}
}

void	draw_line(t_map *map)
{
	int	dx;
	int	dy;

	dx = map->player->x + cos(map->player->rotation_angle) * 10
		- map->player->x;
	dy = map->player->y - sin(map->player->rotation_angle) * 10
		- map->player->y;
	draw_line_2(map, dx, dy);
}

void	create_minimap(t_map *map)
{
	map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3d");
	if (map->win_ptr == NULL)
		exit(EXIT_FAILURE);
	draw_map(map);
	draw_player(map);
	draw_line(map);
	cast_all_rays(map);
	create_3d_walls(map);
	draw_map(map);
	draw_player(map);
	draw_line(map);
	mlx_hook(map->win_ptr, 17, 1L << 17, destroy_window, map);
	mlx_hook(map->win_ptr, 2, 1L << 0, perform_action, map);
	mlx_loop(map->mlx_ptr);
}
