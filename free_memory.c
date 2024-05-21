/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:36:53 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 17:52:20 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_all(t_map *map)
{
	int	i;

	i = 0;
	while (map->player->ray[i] != NULL)
	{
		free(map->player->ray[i]);
		i++;
	}
	free(map->player->ray);
	map->player->ray = NULL;
	i = 0;
	while (map->map_mod[i] != NULL)
	{
		free(map->map_mod[i]);
		i++;
	}
	free(map->map_mod);
	map->map_mod = NULL;
	free(map->player);
	map->player = NULL;
	free(map->map_3d);
	map->map_3d = NULL;
}

int	destroy_window(t_map *map)
{
	free_all(map);
	mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	exit(0);
}
