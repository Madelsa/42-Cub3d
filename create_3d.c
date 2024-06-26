/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:36:45 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/22 14:53:52 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_wall_dimensions(t_map *map, int i)
{
	map->map_3d->perp_distance = map->player->ray[i]->distance
		* cos(map->player->ray[i]->ray_angle - map->player->rotation_angle);
	map->map_3d->distance_proj_plane = (int)(WINDOW_WIDTH / 2)
		/ tan(map->player->fov / 2);
	map->map_3d->proj_wall_height = (int)((TWO_D_TILE_SIZE
				/ map->map_3d->perp_distance) * 
			map->map_3d->distance_proj_plane);
	map->map_3d->wall_top_pixel = (int)(WINDOW_HEIGHT / 2)
		- (map->map_3d->proj_wall_height / 2);
	if (map->map_3d->wall_top_pixel < 0)
		map->map_3d->wall_top_pixel = 0;
	map->map_3d->wall_bottom_pixel = (int)(WINDOW_HEIGHT / 2)
		+ (map->map_3d->proj_wall_height / 2);
	if (map->map_3d->wall_bottom_pixel > WINDOW_HEIGHT)
		map->map_3d->wall_bottom_pixel = WINDOW_HEIGHT;
}

void	determine_texture_offset(t_map *map, int i)
{
	map->map_3d->hit_x = map->player->ray[i]->wall_hit_x * 6.4;
	map->map_3d->hit_y = map->player->ray[i]->wall_hit_y * 6.4;
	if (map->player->ray[i]->was_hit_vertical)
		map->map_3d->tex_x = (int)map->map_3d->hit_y % TILE_SIZE;
	else
		map->map_3d->tex_x = (int)map->map_3d->hit_x % TILE_SIZE;
	if (map->player->ray[i]->is_south_wall)
		map->map_3d->tex_index = 0;
	else if (map->player->ray[i]->is_north_wall)
		map->map_3d->tex_index = 1;
	else if (map->player->ray[i]->is_east_wall)
		map->map_3d->tex_index = 2;
	else if (map->player->ray[i]->is_west_wall)
		map->map_3d->tex_index = 3;
	else
		map->map_3d->tex_index = 0;
}

void	render_wall_slice(t_map *map, int i)
{
	int	y;
	int	distance_from_top;

	y = map->map_3d->wall_top_pixel;
	while (y < map->map_3d->wall_bottom_pixel)
	{
		distance_from_top = y + (map->map_3d->proj_wall_height / 2)
			- ((int)WINDOW_HEIGHT / 2);
		map->map_3d->tex_y = distance_from_top * (TILE_SIZE
				/ map->map_3d->proj_wall_height);
		if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		{
			map->map_3d->image_data[y * WINDOW_WIDTH
				+ i] = map->map_3d->tex_datas[map->map_3d->tex_index]
			[map->map_3d->tex_y * TILE_SIZE + map->map_3d->tex_x];
		}
		y++;
	}
}

void	render_ceiling_and_floor(t_map *map, int i)
{
	int	y;

	y = 0;
	while (y < map->map_3d->wall_top_pixel)
	{
		if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			map->map_3d->image_data[y * WINDOW_WIDTH + i] = map->rgb[1];
		y++;
	}
	y = map->map_3d->wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
	{
		if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
			map->map_3d->image_data[y * WINDOW_WIDTH + i] = map->rgb[0];
		y++;
	}
}

void	create_3d_walls(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		map->map_3d->tex_datas[i] = (unsigned int *)mlx_get_data_addr(
				map->textures[i + 2], &map->map_3d->bits_per_pixel,
				&map->map_3d->size_line, &map->map_3d->endian);
	}
	map->map_3d->buffer = mlx_new_image(map->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	map->map_3d->image_data = (unsigned int *)mlx_get_data_addr(
			map->map_3d->buffer, &map->map_3d->bits_per_pixel,
			&map->map_3d->size_line, &map->map_3d->endian);
	i = -1;
	while (++i < map->no_of_rays)
	{
		calculate_wall_dimensions(map, i);
		determine_texture_offset(map, i);
		render_wall_slice(map, i);
		render_ceiling_and_floor(map, i);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr,
		map->map_3d->buffer, 0, 0);
	mlx_destroy_image(map->mlx_ptr, map->map_3d->buffer);
}
