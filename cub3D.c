/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/10 04:17:18 by mahmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void draw_map(t_map *map)
{
    int x;
    int y;

    y = 0;

    while (map->map[y] != NULL)
    {
        x = 0;
        while (map->map[y][x] != '\0')
        {
            if (map->map[y][x] == '0')
                mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->textures[0],
                    (x * TWO_D_TILE_SIZE), (y * TWO_D_TILE_SIZE));
            else if (map->map[y][x] == '1')
                mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->textures[1],
                    (x * TWO_D_TILE_SIZE), (y * TWO_D_TILE_SIZE));
            x++;
        }
        y++;
    }
}


void draw_player(t_map *map) {

    int draw_start_x = map->player->x - (map->player->width / 2);
    int draw_start_y = map->player->y - (map->player->height / 2);

    int x;
    int y;

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


int assign_images(t_map *map)
{
    map->textures[0] = mlx_xpm_file_to_image(map->mlx_ptr,
            "./textures/white_square_10.xpm", &map->img_width , &map->img_height);
    map->textures[1] = mlx_xpm_file_to_image(map->mlx_ptr,
            "./textures/black_square_10.xpm", &map->img_width, &map->img_height);
    if (map->textures[0] == NULL || map->textures[1] == NULL)
        return (1);
    return (0);
}


int destroy_window(t_map *map)
{
    mlx_destroy_window(map->mlx_ptr, map->win_ptr);
    exit(0);
}

void normalize_angle(double *angle) 
{
    // while (*angle < 0) {
    //     *angle += TWO_PI;
    // }
    // while (*angle >= TWO_PI) {
    //     *angle -= TWO_PI;
    // }
    *angle = remainder(*angle, TWO_PI);
    if (*angle < 0)
        *angle += TWO_PI; 
}

void rotate_line(t_map *map, double angle) {
    map->player->turn_direction = angle;
    map->player->rotation_angle += map->player->turn_direction * map->player->turn_speed; // Subtract instead of add
    
    // Normalize rotation angle to keep it within 0 to 2 * PI
    normalize_angle(&map->player->rotation_angle);
    // printf("%f\n", map->player->rotation_angle); // Print rotation angle for debugging
}


void draw_line(t_map *map) {
    int x0 = map->player->x;  
    int y0 = map->player->y;  
    
    // Calculate endpoint coordinates based on rotation angle
    int x1 = x0 + cos(map->player->rotation_angle) * 10;  
    int y1 = y0 - sin(map->player->rotation_angle) * 10;  

    int dx = x1 - x0;  
    int dy = y1 - y0;  
    int steps;

    if (abs(dy) > abs(dx)) {  
        steps = abs(dy);  
    } else {
        steps = abs(dx);  
    }

    double x_increment = dx / (double)steps;  
    double y_increment = dy / (double)steps; 

    double y = y0;  
    double x = x0;  

    int i = 0;
    while (i <= steps) {
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, (int)x, (int)y, 0xFF0000);  
        y += y_increment;  
        x += x_increment; 
        i++;
    }
}


int check_wall_index(t_map *map, double x, double y)
{
    int next_x = floor(x / TWO_D_TILE_SIZE);
    int next_y = floor(y / TWO_D_TILE_SIZE);

    if (map->map[next_y][next_x] == '1')
        return (1);
    return (0);
    
}


void move_player(t_map *map, int direction) 
{
    // Calculate movement direction based on the angle of the line
    map->player->walk_direction = direction;
    double move_step = map->player->walk_direction * map->player->walk_speed;
    
    double dx = cos(map->player->rotation_angle) * move_step;
    double dy = -sin(map->player->rotation_angle) * move_step;

  

    // Update player position based on direction
    if (check_wall_index(map, map->player->x + dx, map->player->y + dy) == 0)
    {
        map->player->x += dx;
        map->player->y += dy;
    }

}

void draw_line_rays(t_map *map, double x1, double y1) {
    int x0 = map->player->x;  
    int y0 = map->player->y;  
    
    int dx = x1 - x0;  
    int dy = y1 - y0;  
    int steps;

    if (abs(dy) > abs(dx)) {  
        steps = abs(dy);  
    } else {
        steps = abs(dx);  
    }

    double x_increment = dx / (double)steps;  
    double y_increment = dy / (double)steps; 

    double y = y0;  
    double x = x0;  

    int i = 0;
    while (i <= steps) {
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, (int)x, (int)y, 0xFF0000);  
        y += y_increment;  
        x += x_increment; 
        i++;
    }
}

void render_rays(t_map *map)
{
    int i = 0;

    while (i < map->no_of_rays)
    {
        draw_line_rays(map, map->player->ray[i]->wall_hit_x, map->player->ray[i]->wall_hit_y);
        i++;
    }
}

double distance_between_points(t_map *map, double x2, double y2)
{
    return sqrt((x2 - map->player->x) * (x2 - map->player->x) + (y2 - map->player->y) * (y2 - map->player->y));
}




void create_3d_walls(t_map *map)
{
    int bits_per_pixel;
    int size_line;
    int endian;

    // Create an off-screen buffer
    void *buffer = mlx_new_image(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!buffer) {
        // Handle error
        return;
    }

    // Get the address of the buffer and retrieve image data format information
    unsigned int *image_data = (unsigned int *)mlx_get_data_addr(buffer, &bits_per_pixel, &size_line, &endian);

    for (int i = 0; i < map->no_of_rays; i++) {
        float perpDistance = map->player->ray[i]->distance * cos(map->player->ray[i]->ray_angle - map->player->rotation_angle);
        float distanceProjPlane = (WINDOW_WIDTH) / tan(FOV / 2);
        float projectedWallHeight = (TWO_D_TILE_SIZE / perpDistance) * distanceProjPlane;

        int wallStripHeight = (int)projectedWallHeight;

        int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
        // printf("TOP PX: %d\n", wallStripHeight);
        if (wallStripHeight == 0)
            // printf("distance: %f\n", map->player->ray[i]->distance);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

        int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;
        // printf("ray id: %d\n", i);
        // printf("TOP PX: %d\n", wallTopPixel);
        // printf("BOT PX: %d\n\n", wallBottomPixel);
        // Render the wall from wallTopPixel to wallBottomPixel
        for (int y = wallTopPixel; y < wallBottomPixel; y++) {
            // Store the pixel color in the off-screen buffer
            if (i >= 0 && i < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
                image_data[y * WINDOW_WIDTH + i] = 0xFFFFFF; // White color
            }
        }
    }

    // Display the off-screen buffer on the window
    mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, buffer, 0, 0);

    // Destroy the off-screen buffer
    mlx_destroy_image(map->mlx_ptr, buffer);
}



int perform_action(int keycode, t_map *map)
{
    if (keycode == 53)
        destroy_window(map);
    else if (keycode == 123) // Left arrow key
    {
       rotate_line(map, 1); // Rotate counterclockwise map->player->turn_direction = -1
    }
    else if (keycode == 124) // Right arrow key
    {
        rotate_line(map, -1); // Rotate clockwise map->player->walk_direction = 1
    }
    else if (keycode == 126) // Up arrow key
    {
        map->player->walk_direction = 1 ;
        move_player(map, map->player->walk_direction); // Move player forward map->player->walk_direction = 1
    }
    else if (keycode == 125) // Down arrow key
    {
        map->player->walk_direction = -1;
        move_player(map, map->player->walk_direction); // Move player backward map->player->walk_direction = -1
    }
    map->player->walk_direction = 0;
    mlx_clear_window(map->mlx_ptr, map->win_ptr); // Clear the window
    draw_map(map);
    draw_player(map); // Draw the player
    draw_line(map); // Draw the line
    cast_all_rays(map);
    // render_rays(map);
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
    // render_rays(map);
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
    map->mlx_ptr = mlx_init();
    if (map->mlx_ptr == NULL)
        exit(EXIT_FAILURE);
    // map->map_height = 30;
    // map->map_width = 30;
    map->img_height = 64;
    map->img_width = 64;
    map->player = ft_calloc(sizeof(t_player), 1);
    map->no_of_rays = WINDOW_WIDTH; //ray per how many pixels;
    map->player->ray = malloc(sizeof(t_ray *) * map->no_of_rays); // Allocate memory for the array of t_ray pointers
    if (map->player->ray == NULL) {
        // Handle memory allocation failure
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < map->no_of_rays) {
        map->player->ray[i] = malloc(sizeof(t_ray)); // Allocate memory for each t_ray struct
        if (map->player->ray[i] == NULL) {
            // Handle memory allocation failure
            exit(EXIT_FAILURE);
        }
        i++;
    }
    map->player->x = map->map_width / 2;  //update later starting pos
    map->player->y = map->map_height / 2; //update later starting pos
    map->player->width = 3;
    map->player->height = 3;
    map->player->turn_direction = 0;
    map->player->walk_direction = 0;
    map->player->rotation_angle = PI / 2;
    map->player->walk_speed = 5;
    map->player->turn_speed = 15 * (PI / 180);
}

void ft_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; 
}

void replace_chars(t_map *map, int longest_line)
{
    int i = 0;
    while (i < map->map_height) {
    int j = 0;
    while (j < longest_line) {
        // if (ft_strchr("NSEW01", map->map_mod[i][j]) == NULL) {
        //     map->map_mod[i][j] = '1';
        // }
        if (map->map_mod[i][j] != 'N' && map->map_mod[i][j] != 'S' && map->map_mod[i][j] != 'E' && 
        map->map_mod[i][j] != 'W' && map->map_mod[i][j] != '0' && map->map_mod[i][j] != '1')
             map->map_mod[i][j] = '1';
        j++;
    }
    map->map_mod[i][longest_line] = '\0';
    i++;
}
 map->map_mod[i - 1] = NULL;
 map->map_height -= 1;
}

void allocate_map_mod(t_map *map, int longest_line) {
    map->map_mod = malloc(sizeof(char **) * map->map_height + 1);
    int i = 0;
    // int j = 0;
    while (i < map->map_height) {
        map->map_mod[i] = malloc(sizeof(char *) * longest_line + 1);
        ft_strcpy(map->map_mod[i], map->map[i]);
        // printf("%s\n", map->map_mod[i])
        // j++;
        i++;
    }
    // map->map_mod[i] = NULL;
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
      printf("%d\n", map->map_width);
    printf("%d\n", map->map_height);
    return max_length;
}





int	main(int ac, char **av)
{
    t_map map;
    int longest_line;
    if (ac != 2)
		return (1);
	parsing(av[1], &map);
    init_values(&map);
    longest_line = find_longest_line_length(&map);

    allocate_map_mod(&map, longest_line);
    
    int i = 0;
    replace_chars(&map, longest_line);
    while (map.map_mod[i] != NULL)
    {
        printf("%s\n", map.map_mod[i]);
        i++;
    }
    map.map = map.map_mod;
    // int i = 0;
    // while (map.map[i] != NULL)
    // {
    //     printf("%s\n", map.map[i]);
    //     i++;
    // }
    // exit(1);
    assign_images(&map);
    // printf("%d\n", map.map_width);
    // printf("%d\n", map.map_height);
    map.player->x = 1 * map.img_width + map.img_width / 2;
    map.player->y = 3 * map.img_height + map.img_height / 2;
    create_minimap(&map);
    return (0);
}