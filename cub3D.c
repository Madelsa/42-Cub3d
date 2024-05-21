/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 17:50:00 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_map	map;
	int		longest_line;

	if (ac != 2)
		return (1);
	map.mlx_ptr = mlx_init();
	if (map.mlx_ptr == NULL)
		return (1);
	parsing(av[1], &map);
	init_values(&map);
	longest_line = find_longest_line_length(&map);
	allocate_map_mod(&map, longest_line);
	replace_chars(&map, longest_line);
	map.map = map.map_mod;
	map.player->x = (int)map.player->x * TWO_D_TILE_SIZE + (int)(TWO_D_TILE_SIZE
			/ 2);
	map.player->y = (int)map.player->y * TWO_D_TILE_SIZE + (int)(TWO_D_TILE_SIZE
			/ 2);
	create_minimap(&map);
	return (0);
}
