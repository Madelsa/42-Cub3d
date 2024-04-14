/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:39 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/12 17:52:53 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include <math.h>
#include <stdio.h>

#define PI M_PI
#define TWO_PI 2 * M_PI
#define FOV 60 * (PI / 180)

typedef struct s_player
{
    double x;
    double y;
    double width;
    double height;
    int turn_direction;
    int walk_direction;
    double rotation_angle;
    double walk_speed;
    double turn_speed;
}   t_player;

typedef struct s_map
{
    void	*mlx_ptr;
	void	*win_ptr;
    char    map[7][7];
    int		map_width;
	int		map_height;
    int     no_of_rays;
	int		img_width;
	int		img_height;
    void	*textures[2];
    t_player *player;
}	t_map;


#endif