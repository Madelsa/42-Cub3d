/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:16 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/11 16:28:54 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void place_images(t_mlx_data *mlx_data)
// {
//     int x;
//     int y;

//     y = 0;

//     while (y < mlx_data->map_height)
//     {
//         x = 0;
//         while (x < mlx_data->map_width)
//         {
            
//             if (mlx_data->map[y][x] == '0')
//                 mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->textures[0],
// 			x * (mlx_data->img_width), y * (mlx_data->img_height));
//             else if (mlx_data->map[y][x] == '1')
//                 mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->textures[1],
// 			x * (mlx_data->img_width), y * (mlx_data->img_height));
//             x++;
//         }
//         y++;
//     }
// }

// int	assign_images(t_mlx_data *mlx_data)
// {
// 	mlx_data->textures[0] = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
// 			"./textures/white_square.xpm", &mlx_data->img_width, &mlx_data->img_height);
// 	mlx_data->textures[1] = mlx_xpm_file_to_image(mlx_data->mlx_ptr,
// 			"./textures/black_square.xpm", &mlx_data->img_width, &mlx_data->img_height);
// 	if (mlx_data->textures[0] == NULL || mlx_data->textures[1] == NULL)
// 		return (1);
// 	return (0);
// }


// int	destroy_window(t_mlx_data *mlx_data)
// {
// 	mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
// 	exit(0);
// }

// int	perform_action(int keycode, t_mlx_data *mlx_data)
// {
// 	if (keycode == 53)
// 		destroy_window(mlx_data);
// 	return (0);
// }

// void	create_minimap(t_mlx_data *mlx_data)
// {
// 	mlx_data->mlx_ptr = mlx_init();
// 	if (mlx_data->mlx_ptr == NULL)
// 		return ;
// 	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, mlx_data->map_width * mlx_data->img_width, 
//         mlx_data->map_height * mlx_data->img_height, "Cub3d");
// 	if (mlx_data->win_ptr == NULL)
// 		return ;
//      place_images(mlx_data);    
// 	mlx_hook(mlx_data->win_ptr, 17, 1L << 17, destroy_window, mlx_data);
// 	mlx_hook(mlx_data->win_ptr, 2, 1L << 0, perform_action, mlx_data);
//     mlx_clear_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
// 	mlx_loop(mlx_data->mlx_ptr);
// }

// void init_map(t_mlx_data *mlx_data) {
//     char map_init[5][5] = {
//             {'1', '0', '0', '0', '1'},
//             {'1', '0', '1', '0', '1'},
//             {'1', '1', '1', '0', '0'},
//             {'0', '0', '0', '1', '1'},
//             {'1', '1', '0', '0', '1'}
//         };

//     // Copy the values to the map
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             mlx_data->map[i][j] = map_init[i][j];
//         }
//     }

   
//     // Set map width and height
//     // map->map_width = 5;
//     // map->map_height = 5;
// }




// int	main(void)
// {
// 	t_mlx_data mlx_data;
//     assign_images(&mlx_data);
//     mlx_data.map_height = 5;
// 	mlx_data.map_width = 5;
//     mlx_data.img_height = 64;
// 	mlx_data.img_width = 64;
//     init_map(&mlx_data);

// 	create_minimap(&mlx_data);
// }

void draw_square(void *mlx_ptr, void *win_ptr, int x, int y, int size) {
    int i, j;
    for (i = x; i < x + size; i++) {
        for (j = y; j < y + size; j++) {
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, 0xFF0000); // Red color in RGB format
        }
    }
}

void move_square(void *mlx_ptr, void *win_ptr) {
    int x = 0;
    int y = 0;
    
    while (x + SQUARE_SIZE <= WIN_WIDTH && y + SQUARE_SIZE <= WIN_HEIGHT) {
        mlx_clear_window(mlx_ptr, win_ptr);
        draw_square(mlx_ptr, win_ptr, x, y, SQUARE_SIZE);
       usleep(5000);
        x++;
        y++;
    }
}



int main() {
    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Moving Square");

    move_square(mlx_ptr, win_ptr);

    mlx_loop(mlx_ptr);

    return 0;
}