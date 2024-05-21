/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:39 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 18:15:10 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define TILE_SIZE 64
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define TEXTURE_SIZE 720
# define TWO_D_TILE_SIZE 10

typedef struct s_ray
{
	double						ray_angle;
	double						wall_hit_x;
	double						wall_hit_y;
	double						distance;
	double						xint;
	double						yint;
	double						xstep;
	double						ystep;
	double						horz_wall_hit_x;
	double						horz_wall_hit_y;
	double						vert_wall_hit_x;
	double						vert_wall_hit_y;
	int							was_hit_vertical;
	int							is_facing_up;
	int							is_facing_down;
	int							is_facing_left;
	int							is_facing_right;
	int							is_north_wall;
	int							is_south_wall;
	int							is_east_wall;
	int							is_west_wall;
	int							found_horz_wall_hit;
	int							found_vert_wall_hit;
}								t_ray;

typedef struct s_player
{
	double						x;
	double						y;
	double						width;
	double						height;
	int							turn_direction;
	int							walk_direction;
	double						fov;
	double						rotation_angle;
	double						walk_speed;
	double						turn_speed;
	t_ray						**ray;
}								t_player;

typedef struct s_map_3d
{
	unsigned int				*tex_datas[4];
	void						*buffer;
	unsigned int				*image_data;
	double						perp_distance;
	double						distance_proj_plane;
	double						proj_wall_height;
	int							wall_top_pixel;
	int							wall_bottom_pixel;
	int							tex_y;
	double						hit_x;
	double						hit_y;
	int							tex_x;
	int							tex_index;
	int							bits_per_pixel;
	int							size_line;
	int							endian;
	int							d;
}								t_map_3d;

typedef struct s_map
{
	void						*mlx_ptr;
	void						*win_ptr;
	char						**map;
	char						**map_mod;
	int							map_width;
	int							map_height;
	int							window_width;
	int							window_height;
	int							no_of_rays;
	int							img_width;
	int							img_height;
	int							rgb[2];
	void						*textures[6];
	t_player					*player;
	t_map_3d					*map_3d;
}								t_map;

typedef struct s_linked_list_map
{
	char						*row;
	struct s_linked_list_map	*next;
}								t_linked_list_map;

typedef struct s_parsing_map_cp
{
	char						**map_cp;
	int							*num_of_elements_in_each_row;
}								t_parsing_map_cp;

typedef struct s_parsing
{
	int							r[2];
	int							g[2];
	int							b[2];
	int							rgb[2];
	int							wall_texture_fds[4];
	int							main_map_row_num;
	int							six_lines_done[6];
}								t_parsing;

void	normalize_angle(double *angle);
double	distance_between_points(t_map *map, double x2, double y2);
int		check_wall_index(t_map *map, double x, double y);
void	cast_all_rays(t_map *map);
void	find_horz_intercept(t_map *map, double rayAngle, int i);
void	find_vert_intercept(t_map *map, double rayAngle, int i);
void	wall_hit_direction(t_map *map, int i);
void	choose_intercept(t_map *map, double vertHitDistance,
			double horzHitDistance, int i);
void	calculate_distance(t_map *map, double rayAngle, int i);
void	parsing(char *file_name, t_map *map);
int		assign_images(t_map *map, t_parsing *parsing);
void	draw_map(t_map *map);
void	draw_player(t_map *map);
void	draw_line(t_map *map);
void	free_all(t_map *map);
int		destroy_window(t_map *map);
void	replace_chars(t_map *map, int longest_line);
void	allocate_map_mod(t_map *map, int longest_line);
int		find_longest_line_length(t_map *map);
void	create_3d_walls(t_map *map);
int		perform_action(int keycode, t_map *map);
void	create_minimap(t_map *map);
void	init_values(t_map *map);
void	create_3d_walls(t_map *map);

#endif