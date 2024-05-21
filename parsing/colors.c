/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalkaisi <aalkaisi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:33:49 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/21 19:36:21 by aalkaisi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	six_lines_done_and_rgb_init(t_parsing *parsing)
{
	parsing->six_lines_done[0] = 0;
	parsing->six_lines_done[1] = 0;
	parsing->six_lines_done[2] = 0;
	parsing->six_lines_done[3] = 0;
	parsing->six_lines_done[4] = 0;
	parsing->six_lines_done[5] = 0;
	parsing->r[0] = 0;
	parsing->g[0] = 0;
	parsing->b[0] = 0;
	parsing->r[1] = 0;
	parsing->g[1] = 0;
	parsing->b[1] = 0;
}

void	second_if(t_save_colors *s, char **line, t_parsing *parsing)
{
	if (line[s->j][s->i] >= '0' && line[s->j][s->i] <= '9' 
		&& s->num_type == 'r')
	{
		parsing->r[0 + s->k] = line[s->j][s->i] - '0' 
			+ parsing->r[0 + s->k] * 10;
		s->got_a_num = 1;
	}
	else if (line[s->j][s->i] >= '0' && line[s->j][s->i] <= '9' 
		&& s->num_type == 'g')
	{
		parsing->g[0 + s->k] = line[s->j][s->i] - '0' 
			+ parsing->g[0 + s->k] * 10;
		s->got_a_num = 2;
	}
	else if (line[s->j][s->i] >= '0' && line[s->j][s->i] <= '9' 
		&& s->num_type == 'b')
	{
		parsing->b[0 + s->k] = line[s->j][s->i] - '0' 
			+ parsing->b[0 + s->k] * 10;
		s->got_a_num = 3;
	}
	s->i++;
}

int	small_if(t_save_colors *s)
{
	if (s->num_type == 'r')
		s->num_type = 'g';
	else if (s->num_type == 'g')
		s->num_type = 'b';
	else if (s->num_type == 'b')
		return (write(1, "wrong RGB input\n", 16), 1);
	return (0);
}

int	big_while_loop(t_save_colors *s, char **line, t_parsing *parsing)
{
	while (line[s->j] != NULL)
	{
		if (s->got_a_num == 0 && !(line[s->j][s->i] >= '0' 
			&& line[s->j][s->i] <= '9'))
			return (write(1, "wrong RGB input\n", 16), 1);
		else if (!(line[s->j][s->i] >= '0' && line[s->j][s->i] <= '9') 
			&& line[s->j][s->i] != ',' && line[s->j][s->i] != '\0')
			return (write(1, "wrong RGB input\n", 16), 1);
		else if (line[s->j][s->i] == '\0')
		{
			s->j++;
			s->i = 0;
			continue ;
		}
		else if (line[s->j][s->i] == ',')
		{
			if (small_if(s) == 1)
				return (1);
		}
		second_if(s, line, parsing);
	}
	return (0);
}

int	save_colors(int line_type, char **line, t_parsing *parsing)
{
	t_save_colors	s;

	if (line[1] == NULL)
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	s.i = 0;
	s.j = 1;
	s.num_type = 'r';
	s.got_a_num = 0;
	s.k = line_type - 4;
	if ((line_type == 4 && parsing->six_lines_done[4] == 0) 
		|| (line_type == 5 && parsing->six_lines_done[5] == 0))
	{
		if (big_while_loop(&s, line, parsing) == 1)
			return (1);
		if (s.got_a_num != 3)
			return (write(1, "wrong RGB input\n", 16), 1);
		parsing->six_lines_done[4 + s.k] = 1;
	}
	else
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}
