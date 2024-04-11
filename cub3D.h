/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:21:39 by mabdelsa          #+#    #+#             */
/*   Updated: 2024/04/11 16:26:36 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 400
#define SQUARE_SIZE 50

typedef struct s_mlx_data
{
    void	*mlx_ptr;
	void	*win_ptr;
    char     map[5][5];
    int		map_width;
	int		map_height;
	int		img_width;
	int		img_height;
    void	*textures[2];
}	t_mlx_data;

#endif