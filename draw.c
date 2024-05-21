/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:32:07 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/05/21 15:34:27 by mabdelsa         ###   ########.fr       */
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


void draw_player(t_map *map) 
{

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

void draw_line(t_map *map) 
{
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