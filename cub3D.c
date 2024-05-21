/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 15:33:25 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void free_all(t_map *map)
{
    int i;

    i = 0;
    while (map->player->ray[i] != NULL) 
    {
        free(map->player->ray[i]);
        i++;
    }
    free(map->player->ray);
    map->player->ray = NULL;
    i = 0;
    while (map->map_mod[i] != NULL) {
        free(map->map_mod[i]);
        i++;
    }
    free(map->map_mod);
    map->map_mod = NULL;
    free(map->player);
    map->player = NULL;
}






int assign_images(t_map *map, t_parsing *parsing)
{
    map->rgb[0] = parsing->rgb[0];
	map->rgb[1] = parsing->rgb[1];
    map->img_height = 10;
    map->img_width = 10;
    map->textures[0] = mlx_xpm_file_to_image(map->mlx_ptr,
            "./textures_2/white_square_10.xpm", &map->img_width , &map->img_height);
    map->textures[1] = mlx_xpm_file_to_image(map->mlx_ptr,
            "./textures_2/black_square_10.xpm", &map->img_width, &map->img_height);
    if (map->textures[0] == NULL || map->textures[1] == NULL)
        return (1);
    return (0);
}


int destroy_window(t_map *map)
{
    free_all(map);
    mlx_destroy_window(map->mlx_ptr, map->win_ptr);
    exit(0);
}

void normalize_angle(double *angle) 
{
    *angle = remainder(*angle, TWO_PI);
    if (*angle < 0)
        *angle += TWO_PI; 
}

void rotate_line(t_map *map, double angle) {
    map->player->turn_direction = angle;
    map->player->rotation_angle += map->player->turn_direction * map->player->turn_speed; // Subtract instead of add
    normalize_angle(&map->player->rotation_angle);
}





int check_wall_index(t_map *map, double x, double y)
{
    int next_x = floor(x / TWO_D_TILE_SIZE);
    int next_y = floor(y / TWO_D_TILE_SIZE);

    if (map->map[next_y][next_x] == '1')
        return (1);
    return (0);
    
}


double distance_between_points(t_map *map, double x2, double y2)
{
    return sqrt((x2 - map->player->x) * (x2 - map->player->x) + (y2 - map->player->y) * (y2 - map->player->y));
}




void create_3d_walls(t_map *map)
{
    int bits_per_pixel, size_line, endian;

    // Get texture data addresses
    unsigned int *tex_datas[4];
    for (int t = 0; t < 4; t++) {
        tex_datas[t] = (unsigned int *)mlx_get_data_addr(map->textures[t + 2], &bits_per_pixel, &size_line, &endian);
    }

    // Create an off-screen buffer
    void *buffer = mlx_new_image(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!buffer) {
        // Handle error
        for (int t = 0; t < 4; t++) {
            mlx_destroy_image(map->mlx_ptr, map->textures[t + 2]);
        }
        return;
    }

    // Get the address of the buffer and retrieve image data format information
    unsigned int *image_data = (unsigned int *)mlx_get_data_addr(buffer, &bits_per_pixel, &size_line, &endian);
    
    for (int i = 0; i < map->no_of_rays; i++) {
        float perpDistance = map->player->ray[i]->distance * cos(map->player->ray[i]->ray_angle - map->player->rotation_angle);
        float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        float projectedWallHeight = (TWO_D_TILE_SIZE / perpDistance) * distanceProjPlane;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        if (wallTopPixel < 0) wallTopPixel = 0;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        if (wallBottomPixel > WINDOW_HEIGHT) wallBottomPixel = WINDOW_HEIGHT;

        // Calculate the texture offset
        float hit_x = map->player->ray[i]->wall_hit_x; // Assuming you have this info
        float hit_y = map->player->ray[i]->wall_hit_y; // Assuming you have this info
        int tex_x, tex_index;

        if (map->player->ray[i]->was_hit_vertical) {
            tex_x = (int)hit_y % TWO_D_TILE_SIZE;
        } else {
            tex_x = (int)hit_x % TWO_D_TILE_SIZE;
        }
        tex_x = (tex_x * 720) / TWO_D_TILE_SIZE; // Scale to texture width

        // Determine texture index based on wall direction
        if (map->player->ray[i]->is_south_wall) {
            tex_index = 0; // North wall texture
        } else if (map->player->ray[i]->is_north_wall) {
            tex_index = 1; // South wall texture
        } else if (map->player->ray[i]->is_east_wall) {
            tex_index = 2; // East wall texture
        } else if (map->player->ray[i]->is_west_wall) {
            tex_index = 3; // West wall texture
        } else {
            tex_index = 0; // Default to north wall texture
        }

        // Render the wall from wallTopPixel to wallBottomPixel with texture
        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
            int d = y * 256 - WINDOW_HEIGHT * 128 + wallStripHeight * 128; // 256 and 128 factors to avoid floats
            int tex_y = ((d * 720) / wallStripHeight) / 256;
            if (tex_y < 0) tex_y = 0;
            if (tex_y >= 720) tex_y = 720 - 1;

            if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
                image_data[y * WINDOW_WIDTH + i] = tex_datas[tex_index][tex_y * 720 + tex_x];
            }
        }

        // Render the ceiling
        for (int y = 0; y < wallTopPixel; y++) {
            if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
                image_data[y * WINDOW_WIDTH + i] = map->rgb[1];
            }
        }

        // Render the floor
        for (int y = wallBottomPixel; y < WINDOW_HEIGHT; y++) {
            if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
                image_data[y * WINDOW_WIDTH + i] = map->rgb[0];
            }
        }
    }

    // Display the off-screen buffer on the window
    mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, buffer, 0, 0);

    // Destroy the off-screen buffer
    mlx_destroy_image(map->mlx_ptr, buffer);
}



void move_player(t_map *map, int direction, int strafe)
{
    double move_step = map->player->walk_speed;
    double dx, dy;

    if (strafe == 0) { // Forward or backward
        dx = cos(map->player->rotation_angle) * direction * move_step;
        dy = -sin(map->player->rotation_angle) * direction * move_step;
    } else { // Left or right (strafing)
        dx = cos(map->player->rotation_angle - (M_PI_2 * strafe)) * move_step;
        dy = -sin(map->player->rotation_angle - (M_PI_2 * strafe)) * move_step;
    }

    // Update player position based on direction
    if (check_wall_index(map, map->player->x + dx * 1.1, map->player->y + dy * 1.1) == 0)
    {
        map->player->x += dx;
        map->player->y += dy;
    }
}
int perform_action(int keycode, t_map *map)
{
    if (keycode == 53) {
        destroy_window(map);
    } else if (keycode == 123) { // Left arrow key
        rotate_line(map, 1); // Rotate counterclockwise
    } else if (keycode == 124) { // Right arrow key
        rotate_line(map, -1); // Rotate clockwise
    } else if (keycode == 13) { // W arrow key
        move_player(map, 1, 0); // Move player forward
    } else if (keycode == 1) { // S arrow key
        move_player(map, -1, 0); // Move player backward
    } else if (keycode == 0) { // 'A' key for strafing left
        move_player(map, 1, -1); // Strafe player left
    } else if (keycode == 2) { // 'D' key for strafing right
        move_player(map, 1, 1); // Strafe player right
    }

    map->player->walk_direction = 0;
    mlx_clear_window(map->mlx_ptr, map->win_ptr); // Clear the window
    draw_map(map);
    draw_player(map); // Draw the player
    draw_line(map); // Draw the line
    cast_all_rays(map);
    create_3d_walls(map);
    draw_map(map);
    draw_player(map); // Draw the player
    draw_line(map); // Draw the line

    return (0);
}


void create_minimap(t_map *map)
{
    map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_WIDTH , 
        WINDOW_HEIGHT, "Cub3d");
    if (map->win_ptr == NULL)
        exit(EXIT_FAILURE);
    draw_map(map);
    draw_player(map);
    draw_line(map);
    cast_all_rays(map);
    create_3d_walls(map);
    draw_map(map);
    draw_player(map); // Draw the player
    draw_line(map); // Draw the line
    mlx_hook(map->win_ptr, 17, 1L << 17, destroy_window, map);
    mlx_hook(map->win_ptr, 2, 1L << 0, perform_action, map);
    mlx_loop(map->mlx_ptr);
}



void init_values(t_map *map)
{
    // (void)parse;
  
    map->img_height = 10;
    map->img_width = 10;
    map->player = malloc(sizeof(t_player) * 1);
    map->no_of_rays = WINDOW_WIDTH; //ray per how many pixels;
    map->player->ray = malloc(sizeof(t_ray *) * (map->no_of_rays + 1)); // Allocate memory for the array of t_ray pointers
    int i = 0;
    while (i < map->no_of_rays) {
        map->player->ray[i] = malloc(sizeof(t_ray));
        i++;
    }
    map->player->ray[i] = NULL;
    map->player->width = 3;
    map->player->height = 3;
    map->player->turn_direction = 0;
    map->player->walk_direction = 0;
    map->player->rotation_angle = PI / 2;
    map->player->walk_speed = 4;
    map->player->turn_speed = 15 * (PI / 180);
}


void replace_chars(t_map *map, int longest_line)
{
    int i = 0;
    while (i < map->map_height) 
    {
        int j = 0;
        while (j < longest_line) {
            if (map->map_mod[i][j] != 'N' && map->map_mod[i][j] != 'S' && map->map_mod[i][j] != 'E' && 
            map->map_mod[i][j] != 'W' && map->map_mod[i][j] != '0' && map->map_mod[i][j] != '1')
                map->map_mod[i][j] = '1';
              if (map->map_mod[i][j] == 'N' || map->map_mod[i][j] == 'S' || map->map_mod[i][j] == 'E' || 
            map->map_mod[i][j] == 'W')
            {
                map->player->x = j;
                map->player->y = i;
                if (map->map_mod[i][j] == 'S')
                    map->player->rotation_angle = (3 * PI) / 2;
                else if (map->map_mod[i][j] == 'E')
                    map->player->rotation_angle = 0;
                else if (map->map_mod[i][j] == 'W')
                    map->player->rotation_angle = PI;
                map->map_mod[i][j] = '0';
            }
            j++;
        }
    map->map_mod[i][longest_line] = '\0';
    i++;
}
 map->map_height -= 1;
}


void allocate_map_mod(t_map *map, int longest_line) {
    map->map_mod = malloc(sizeof(char **) * (map->map_height + 1)); // Allocate memory for map_height + 1 pointers
    int i = 0;
    while (i < map->map_height) {
        map->map_mod[i] = malloc(sizeof(char *) * (longest_line + 1)); // Allocate memory for longest_line + 1 characters
        ft_strcpy(map->map_mod[i], map->map[i]);
        i++;
    }
    map->map_mod[i] = NULL; // Set the last pointer to NULL
}


int find_longest_line_length(t_map *map) {
    int max_length = 0;
    int i = 0;
    while (map->map[i] != NULL) {
        int length = ft_strlen(map->map[i]);
        if (length > max_length) {
            max_length = length;
        }
        i++;
    }
    map->map_height = i;
    map->map_width = max_length;
    return max_length;
}





int	main(int ac, char **av)
{
    t_map map;
    int longest_line;
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
    map.player->x = (int)map.player->x * TWO_D_TILE_SIZE + (int)(TWO_D_TILE_SIZE / 2);
    map.player->y = (int)map.player->y  * TWO_D_TILE_SIZE + (int)(TWO_D_TILE_SIZE / 2);
    create_minimap(&map);
    return (0);
}