/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:39 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/30 13:21:32 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

# define PI M_PI
# define TWO_PI 2 * M_PI
# define FOV 60 * (PI / 180)
#define FALSE 0
#define TRUE 1
# define TILE_SIZE 64


typedef struct s_ray
{
	double ray_angle;
	double wall_hit_x;
	double wall_hit_y;
	double distance;
	int	was_hit_vertical;
	int is_ray_facing_up;
	int is_ray_facing_down;
	int is_ray_facing_left;
	int is_ray_facing_right;
	int wall_hit_content;
	int is_north_wall;
	int is_south_wall;
	int is_east_wall;
	int is_west_wall;

}				t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		width;
	double		height;
	int			turn_direction;
	int			walk_direction;
	double		rotation_angle;
	double		walk_speed;
	double		turn_speed;
	t_ray		**ray;
}				t_player;

typedef struct s_map
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		map[7][7];
	int			map_width;
	int			map_height;
	int			no_of_rays;
	int			img_width;
	int			img_height;
	void		*textures[2];
	t_player	*player;
}				t_map;

#endif