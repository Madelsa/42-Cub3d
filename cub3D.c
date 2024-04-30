/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/30 13:22:44 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"





void draw_map(t_map *map)
{
    int x;
    int y;

    y = 0;

    while (y < map->map_height)
    {
        x = 0;
        while (x < map->map_width)
        {
            if (map->map[y][x] == '0')
                mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->textures[0],
                    (x * map->img_width), (y * map->img_height));
            else if (map->map[y][x] == '1')
                mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->textures[1],
                    (x * map->img_width), (y * map->img_height));
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
            "./textures/white_square.xpm", &map->img_width , &map->img_height);
    map->textures[1] = mlx_xpm_file_to_image(map->mlx_ptr,
            "./textures/black_square.xpm", &map->img_width, &map->img_height);
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
    printf("%f\n", map->player->rotation_angle); // Print rotation angle for debugging
}


void draw_line(t_map *map) {
    int x0 = map->player->x;  
    int y0 = map->player->y;  
    
    // Calculate endpoint coordinates based on rotation angle
    int x1 = x0 + cos(map->player->rotation_angle) * 40;  
    int y1 = y0 - sin(map->player->rotation_angle) * 40;  

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
    int next_x = floor(x / 64);
    int next_y = floor(y / 64);

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

   printf("OLD position: (%f, %f)\n", (map->player->x /64), (map->player->y/64));

    // Update player position based on direction
    if (check_wall_index(map, map->player->x + dx, map->player->y + dy) == 0)
    {
        map->player->x += dx;
        map->player->y += dy;
    }

    printf("New position: (%f, %f)\n", (floor((map->player->x + dx )/ 64)), (floor((map->player->y + dy)/ 64)));
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



void cast_ray(t_map *map, double rayAngle, int stripId) {

    int window_width, window_height;
    window_width = map->map_width * TILE_SIZE;
    window_height = map->map_height * TILE_SIZE;
    normalize_angle(&rayAngle);
    
    int isRayFacingUp = rayAngle > 0 && rayAngle < PI;
    int isRayFacingDown = !isRayFacingUp;

    int isRayFacingLeft = rayAngle > PI / 2 && rayAngle < (3 * PI) / 2;
    int isRayFacingRight = !isRayFacingLeft;

    double xintercept, yintercept;
    double xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = FALSE;
    double horzWallHitX = 0;
    double horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(map->player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = map->player->x + (yintercept - map->player->y) / tan(-rayAngle); // Invert rotation here

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(-rayAngle); // Invert rotation here
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= window_width && nextHorzTouchY >= 0 && nextHorzTouchY <= window_height) {
        double xToCheck = nextHorzTouchX;
        double yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (check_wall_index(map, xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    
    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = FALSE;
    double vertWallHitX = 0;
    double vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(map->player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = map->player->y + (xintercept - map->player->x) * tan(-rayAngle); // Invert rotation here

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(-rayAngle); // Invert rotation here
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= window_width && nextVertTouchY >= 0 && nextVertTouchY <= window_height) {
        double xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        double yToCheck = nextVertTouchY;
        
        if (check_wall_index(map, xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            // vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    // Calculate both horizontal and vertical hit distances and choose the smallest one
    double horzHitDistance = foundHorzWallHit
        ? distance_between_points(map, horzWallHitX, horzWallHitY)
        : INT_MAX;
    double vertHitDistance = foundVertWallHit
        ? distance_between_points(map, vertWallHitX, vertWallHitY)
        : INT_MAX;

    if (vertHitDistance < horzHitDistance) {
        map->player->ray[stripId]->distance = vertHitDistance;
        map->player->ray[stripId]->wall_hit_x = vertWallHitX;
        map->player->ray[stripId]->wall_hit_y = vertWallHitY;
        map->player->ray[stripId]->wall_hit_content = vertWallContent;
        map->player->ray[stripId]->was_hit_vertical = 1;
    } else {
        map->player->ray[stripId]->distance = horzHitDistance;
        map->player->ray[stripId]->wall_hit_x = horzWallHitX;
        map->player->ray[stripId]->wall_hit_y = horzWallHitY;
        map->player->ray[stripId]->wall_hit_content = horzWallContent;
        map->player->ray[stripId]->was_hit_vertical = 0;
    }
    map->player->ray[stripId]->ray_angle = rayAngle;
    map->player->ray[stripId]->is_ray_facing_down = isRayFacingDown;
    map->player->ray[stripId]->is_ray_facing_up = isRayFacingUp;
    map->player->ray[stripId]->is_ray_facing_left = isRayFacingLeft;
    map->player->ray[stripId]->is_ray_facing_right = isRayFacingRight;
    


    map->player->ray[stripId]->is_north_wall = 0;
    map->player->ray[stripId]->is_south_wall = 0;
    map->player->ray[stripId]->is_east_wall = 0;
    map->player->ray[stripId]->is_west_wall = 0;

    if (isRayFacingUp && map->player->ray[stripId]->was_hit_vertical == 0)
        map->player->ray[stripId]->is_north_wall = 1;
    else if (isRayFacingDown && map->player->ray[stripId]->was_hit_vertical == 0)
        map->player->ray[stripId]->is_south_wall = 1;
    else if (isRayFacingRight && map->player->ray[stripId]->was_hit_vertical == 1)
        map->player->ray[stripId]->is_east_wall = 1;
    else if (isRayFacingLeft && map->player->ray[stripId]->was_hit_vertical == 1)
        map->player->ray[stripId]->is_west_wall = 1;
}






void cast_all_rays(t_map *map)
{
    double ray_angle = map->player->rotation_angle - (FOV / 2);
    
    int i = 0;
    while (i < map->no_of_rays)
    {
        cast_ray(map, ray_angle, i);
        printf("Ray ID: %d Wall Hit: %d %d% d% d\n", i, map->player->ray[i]->is_north_wall,  map->player->ray[i]->is_south_wall,  map->player->ray[i]->is_east_wall,  map->player->ray[i]->is_west_wall);
        ray_angle += FOV / map->no_of_rays ;
        i++;
    }
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
    render_rays(map);


    return (0);
}


void create_minimap(t_map *map)
{
    map->win_ptr = mlx_new_window(map->mlx_ptr, map->map_width * map->img_width, 
        map->map_height * map->img_height, "Cub3d");
    if (map->win_ptr == NULL)
        exit(EXIT_FAILURE);
    draw_map(map);
    draw_player(map);
    draw_line(map);
    cast_all_rays(map);
    render_rays(map);
    mlx_hook(map->win_ptr, 17, 1L << 17, destroy_window, map);
    mlx_hook(map->win_ptr, 2, 1L << 0, perform_action, map);
    mlx_loop(map->mlx_ptr);
}

void init_map(t_map *map) {
    char map_init[7][7] = {
            {'1', '1', '1', '1', '1', '1','1'},
            {'1', '0', '1', '0', '0', '1','1'},
            {'1', '1', '1', '0', '0', '0','1'},
            {'1', '0', '0', '0', '0', '1','1'},
            {'1', '1', '0', '0', '0', '1','1'},
            {'1', '1', '0', '0', '0', '1','1'},
            {'1', '1', '1', '1', '1', '1','1'},
        };

    // Copy the values to the map
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            map->map[i][j] = map_init[i][j];
        }
    }
}

void init_values(t_map *map)
{
    map->mlx_ptr = mlx_init();
    if (map->mlx_ptr == NULL)
        exit(EXIT_FAILURE);
    map->map_height = 7;
    map->map_width = 7;
    map->img_height = 64;
    map->img_width = 64;
    map->player = ft_calloc(sizeof(t_player), 1);
    map->no_of_rays = (map->map_width * map->img_width) / 50; //ray per how many pixels;
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
    map->player->width = 10;
    map->player->height = 10;
    map->player->turn_direction = 0;
    map->player->walk_direction = 0;
    map->player->rotation_angle = PI / 2;
    map->player->walk_speed = 10;
    map->player->turn_speed = 15 * (PI / 180);
}

int	main(void)
{
    t_map map;
    init_values(&map);
    assign_images(&map);
    init_map(&map);
    map.player->x = 3 * map.img_width + map.img_width / 2;
    map.player->y = 2 * map.img_height + map.img_height / 2;
    create_minimap(&map);
    return (0);
}