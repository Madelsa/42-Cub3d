/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelsa <mabdelsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:20:45 by aalkaisi          #+#    #+#             */
/*   Updated: 2024/05/10 10:38:50 by mabdelsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "../cub3D.h"

// typedef struct s_map
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	char		**map;
// 	void		*textures[4];
// 	// t_player	*player;
// }				t_map;

// typedef struct s_linked_list_map
// {
// 	char						*row;
// 	struct s_linked_list_map	*next;
// }	t_linked_list_map;

// typedef struct s_parsing_map_cp
// {
// 	char	**map_cp;
// 	int		*num_of_elements_in_each_row;
// }	t_parsing_map_cp;

// typedef struct s_parsing
// {
// 	int	r[2];
// 	int	g[2];
// 	int	b[2];
// 	int	rgb[2];
// 	int	wall_texture_fds[4];
// 	int	main_map_row_num;
// 	int	six_lines_done[6];
// }	t_parsing;

void	printing(char **map)
{
	int i = 0;
	int j = 0;

	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			// printf("%c", map[i][j]);
			j++;
		}
		// printf("\n");
		i++;
	}
}

static char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
		free((char *)s1);
	return (str);
}

static char	*read_buffer(int fd, char *stored)
{
	char	*buff;
	int		chars_read;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == NULL)
		return (NULL);
	chars_read = 1;
	while (chars_read > 0 && ft_strchr(stored, '\n') == NULL)
	{
		chars_read = read(fd, buff, BUFFER_SIZE);
		if (chars_read == -1 || (chars_read == 0 && (stored == NULL
					|| stored[0] == '\0')))
			return (free(buff), free(stored), NULL);
		buff[chars_read] = '\0';
		stored = ft_strjoin_gnl(stored, buff);
	}
	return (free(buff), stored);
}

static char	*filter_stored(char *stored)
{
	int		i;
	char	*str;

	i = 0;
	while (stored[i] != '\0' && stored[i] != '\n')
		i++;
	if (stored[i] == '\n' || stored[i] == '\0')
		str = ft_substr(stored, 0, i + 1);
	else
		return (NULL);
	return (str);
}

static char	*update_stored(char *stored)
{
	int		i;
	char	*str;

	i = 0;
	while (stored[i] != '\0' && stored[i] != '\n')
		i++;
	if (stored[i] == '\0')
		return (free(stored), NULL);
	str = ft_strdup(stored + i + 1);
	if (!str[0])
		return (free(str), free(stored), NULL);
	return (free(stored), str);
}

char	*get_next_line(int fd)
{
	static char	*stored[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	stored[fd] = read_buffer(fd, stored[fd]);
	if (stored[fd] == NULL)
		return (NULL);
	line = filter_stored(stored[fd]);
	if (line == NULL)
		return (NULL);
	stored[fd] = update_stored(stored[fd]);
	return (line);
}

void	free_map(t_linked_list_map *a)
{
	t_linked_list_map	*c;

	c = a;
	while (a != NULL)
	{
		c = c->next;
		free(a->row);
		free(a);
		a = c;
	}
}

void	print_linked_list(t_linked_list_map *a)
{
	t_linked_list_map	*c;

	c = a;
	while (c != NULL)
	{
		// printf("%s\n", c->row);
		c = c->next;
	}
}

void	free_list_str(char	**two_d_map)
{
	int	i;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		free(two_d_map[i]);
		i++;
	}
	free(two_d_map);
}

// int	is_rectangle(t_map *map)
// {
// 	t_map	*temp_map;
// 	int		row;
// 	int		col_1;
// 	int		col;

// 	temp_map = map;
// 	row = 0;
// 	col_1 = ft_strlen(temp_map->row);
// 	while (temp_map != NULL)
// 	{
// 		row++;
// 		col = ft_strlen(temp_map->row);
// 		if (col != col_1)
// 			return (0);
// 		temp_map = temp_map->next;
// 	}
// 	if (col_1 < 3 || row < 3)
// 		return (0);
// 	return (1);
// }

// int	check_bound_block2(t_map *temp_map, int i)
// {
// 	temp_map = temp_map->next;
// 	while (temp_map->next != NULL)
// 	{
// 		if (!(temp_map->row[0] == '1' && 
// 				temp_map->row[ft_strlen(temp_map->row) - 1] == '1'))
// 			return (0);
// 		temp_map = temp_map->next;
// 	}
// 	i = 0;
// 	while (temp_map->row[i] != '\0' && temp_map != NULL)
// 	{
// 		if (temp_map->row[i] != '1')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	check_bound(t_map *map)
// {
// 	t_map	*temp_map;
// 	int		i;

// 	temp_map = map;
// 	i = 0;
// 	while (temp_map->row[i] != '\0' && temp_map != NULL)
// 	{
// 		if (temp_map->row[i] != '1')
// 			return (0);
// 		i++;
// 	}
// 	return (check_bound_block2(temp_map, i));
// }

int	is_available_block2(char **two_d_map, int p_count)
{
	int	i;
	int	j;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		j = 0;
		while (two_d_map[i][j] != '\0')
		{
			if (two_d_map[i][j] == 'N' || two_d_map[i][j] == 'S' 
				|| two_d_map[i][j] == 'E' || two_d_map[i][j] == 'W')
				p_count++;
			j++;
		}
		i++;
	}
	if (p_count == 1)
		return (1);
	return (0);
}

int	is_available(char **two_d_map)
{
	int		p_count;

	p_count = 0;
	return (is_available_block2(two_d_map, p_count));
}

int	is_valid(char **two_d_map)
{
	int	i;
	int	j;

	i = 0;
	while (two_d_map[i] != NULL)
	{
		j = 0;
		while (two_d_map[i][j] != '\0')
		{
			if (two_d_map[i][j] != '1' && two_d_map[i][j] != '0' && 
			two_d_map[i][j] != ' ' && two_d_map[i][j] != 'N' && 
			two_d_map[i][j] != 'S' && two_d_map[i][j] != 'E' && 
			two_d_map[i][j] != 'W')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	map_copy_block2(char **two_d_map, t_parsing_map_cp *map_cp, int j)
{
	int	i;

	j = 0;
	while (two_d_map[j] != NULL)
	{
		i = 0;
		// printf("%dhhhhhh%s\n", j, two_d_map[j]);
		map_cp->map_cp[j] = malloc(ft_strlen(two_d_map[j]) + 1);
		map_cp->num_of_elements_in_each_row[j] = ft_strlen(two_d_map[j]);
		if (map_cp->map_cp[j] == NULL)
		{
			free(map_cp->num_of_elements_in_each_row);
			free_list_str(two_d_map);
			free_list_str(map_cp->map_cp);
			free(map_cp);
			exit(1);
		}
		while (two_d_map[j][i] != '\0')
		{
			map_cp->map_cp[j][i] = two_d_map[j][i];
			i++;
		}
		map_cp->map_cp[j][i] = '\0';
		j++;
	}
	map_cp->map_cp[j] = NULL;
}

t_parsing_map_cp	*map_copy(char **two_d_map)
{
	t_parsing_map_cp	*map_cp;
	int					j;

	map_cp = malloc(sizeof(t_parsing_map_cp));
	if (map_cp == NULL)
	{
		free_list_str(two_d_map);
		exit(1);
	}
	j = 0;
	while (two_d_map[j] != NULL)
		j++;
	map_cp->map_cp = malloc((j + 1) * sizeof(char *));
	if (map_cp->map_cp == NULL)
	{
		free(map_cp);
		free_list_str(two_d_map);
		exit(1);
	}
	map_cp->num_of_elements_in_each_row = malloc(j * sizeof(int));
	if (map_cp->num_of_elements_in_each_row == NULL)
	{
		free_list_str(two_d_map);
		free(map_cp->map_cp);
		free(map_cp);
		exit(1);
	}
	map_copy_block2(two_d_map, map_cp, j);
	return (map_cp);
}

void	index_player(char **map_cp, int *row, int *col)
{
	*row = 0;
	while (map_cp[*row] != NULL)
	{
		*col = 0;
		while (map_cp[*row][*col] != '\0')
		{
			if (map_cp[*row][*col] == 'S' || map_cp[*row][*col] == 'N' || map_cp[*row][*col] == 'E' || map_cp[*row][*col] == 'W')
				return ;
			(*col)++;
		}
		(*row)++;
	}
}

// int	all_reachable(char **map_cp)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	j = 1;
// 	while (map_cp[i] != NULL)
// 	{
// 		j = 0;
// 		while (map_cp[i][j] != '\0')
// 		{
// 			if (map_cp[i][j] == 'C' || map_cp[i][j] == 'E')
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

int	is_reach(t_parsing_map_cp *map_cp, int row, int col)
{
	// printf("%d, %p\n", row, map_cp[row]);
	if (map_cp->map_cp[row] == NULL)
		return (1);
	if (map_cp->map_cp[row][col] == '1' || map_cp->map_cp[row][col] == 'F')
		return (0);
	else if (map_cp->map_cp[row][col] == ' ' 
	|| map_cp->map_cp[row][col] == '\0' || row == 0 || col == 0)
		return (1);
	else
		map_cp->map_cp[row][col] = 'F';
	// if (all_reachable(map_cp) == 1)
	// 	return (1);
	// printing(map_cp->map_cp);
	if (map_cp->num_of_elements_in_each_row[row + 1] < col 
		|| map_cp->num_of_elements_in_each_row[row - 1] < col)
		return (1);
	// else if (map_cp->num_of_elements_in_each_row[row + 1] < col)
	// 	return (is_reach(map_cp, row - 1, col) | is_reach(map_cp, row, col + 1) 
	// 		| is_reach(map_cp, row, col - 1));
	// else if (map_cp->num_of_elements_in_each_row[row - 1] < col)
	// 	return (is_reach(map_cp, row + 1, col) | is_reach(map_cp, row, col + 1) 
	// 		| is_reach(map_cp, row, col - 1));
	return (is_reach(map_cp, row + 1, col) | is_reach(map_cp, row - 1, col) 
		| is_reach(map_cp, row, col + 1) | is_reach(map_cp, row, col - 1));
}

int	is_reachable(char **two_d_map)
{
	t_parsing_map_cp	*map_cp;
	int					row;
	int					col;
	int					res;

	map_cp = map_copy(two_d_map);
	if (map_cp == NULL)
	{
		free_list_str(two_d_map);
		exit(1);
	}
	row = 0;
	col = 0;
	index_player(map_cp->map_cp, &row, &col);
	res = is_reach(map_cp, row, col);
	printing(map_cp->map_cp);
	free_list_str(map_cp->map_cp);
	free(map_cp->num_of_elements_in_each_row);
	free(map_cp);
	return (res);
}

char	error(char **two_d_map)
{
	if (is_valid(two_d_map) == 0)
	{
		write(1, "Error\n", 6);
		write(1, "The map should have only 1, 0, N, S, E or W symbols\n", 52);
	}
	else if (is_available(two_d_map) == 0)
		write(1, "Error\nThe map should has 1 Player\n", 34);
	else if (is_reachable(two_d_map) == 1)
		write(1, "Error\nThe Player should be inside the walls\n", 44);
	else
		return ('Y');
	return ('N');
}

int	check_extension(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i >= 4 && file_name[i - 1] == 'b' && file_name[i - 2] == 'u' 
		&& file_name[i - 3] == 'c' && file_name[i - 4] == '.')
	{
		return (1);
	}
	return (0);
}



void	empty_map(int fd)
{
	write(1, "Error\n", 6);
	write(1, "The map file is empty\n", 22);
	close(fd);
	exit(1);
}

void	building_map_block2(t_linked_list_map **linked_list_map, 
t_linked_list_map *new_row, t_linked_list_map **last_row, int i)
{
	if (i == 0)
	{
		*linked_list_map = new_row;
		*last_row = new_row;
	}
	else
	{
		(*last_row)->next = new_row;
		*last_row = (*last_row)->next;
	}
}

t_linked_list_map	*building_map(t_linked_list_map *linked_list_map, int fd)
{
	t_linked_list_map	*new_row;
	t_linked_list_map	*last_row;
	char				*temp_str;
	int					i;

	temp_str = get_next_line(fd);
	if (temp_str == NULL)
		empty_map(fd);
	i = 0;
	while (temp_str != NULL)
	{
		new_row = malloc(sizeof(t_linked_list_map));
		if (new_row == NULL)
		{
			free_map(linked_list_map);
			exit(1);
		}
		building_map_block2(&linked_list_map, new_row, &last_row, i);
		last_row->row = temp_str;
		last_row->next = NULL;
		temp_str = get_next_line(fd);
		i++;
	}
	return (linked_list_map);
}

t_linked_list_map	*trim_map(t_linked_list_map *linked_list_map)
{
	t_linked_list_map	*temp_map;

	temp_map = linked_list_map;
	while (temp_map != NULL)
	{
		// printf("lol%s\n", temp_map->row);
		if (temp_map->row[ft_strlen(temp_map->row) - 1] == '\n')
			temp_map->row[ft_strlen(temp_map->row) - 1] = '\0';
		// printf("ccccc%s\n", temp_map->row);
		temp_map = temp_map->next;
	}
	return (linked_list_map);
}





void	conv_tow_d_map_block2(t_linked_list_map *temp_map2, 
char **two_d_map, int i, t_linked_list_map *map)
{
	int		j;

	i = 0;
	while (temp_map2 != NULL)
	{
		two_d_map[i] = malloc(ft_strlen(temp_map2->row) + 1);
		if (two_d_map[i] == NULL)
		{
			free_list_str(two_d_map);
			free_map(map);
			exit(0);
		}
		j = 0;
		while (temp_map2->row[j] != '\0')
		{
			two_d_map[i][j] = temp_map2->row[j];
			j++;
		}
		two_d_map[i][j] = '\0';
		temp_map2 = temp_map2->next;
		i++;
	}
	two_d_map[i] = NULL;
}

char	**conv_two_d_map(t_linked_list_map *map, char **two_d_map, 
	int main_map_row_num)
{
	t_linked_list_map	*temp_map;
	t_linked_list_map	*temp_map2;
	int		i;

	temp_map = map;
	i = 0;
	while (i < main_map_row_num)
	{
		temp_map = temp_map->next;
		i++;
	}
	temp_map2 = temp_map;
	i = 0;
	while (temp_map != NULL)
	{
		temp_map = temp_map->next;
		i++;
	}
	two_d_map = malloc((i + 1) * sizeof(char *));
	if (two_d_map == NULL)
	{
		free_map(map);
		exit(1);
	}
	i = 0;
	conv_tow_d_map_block2(temp_map2, two_d_map, i, map);
	return (two_d_map);
}

void	six_lines_done_and_RGB_init(t_parsing *parsing)
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

void	free_double_pointer(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

int	read_wall_texture_block_2(int wall_direction, char **line, t_parsing *parsing)
{
	if (line[1] != NULL && line[2] == NULL && wall_direction == 2 
		&& parsing->six_lines_done[2] == 0)
	{
		parsing->wall_texture_fds[2] = open(line[1], O_RDONLY);
		if (parsing->wall_texture_fds[2] < 0)
			return (write(1, "Error\nThere is no texture with this name\n", 41)
				, 1);
		parsing->six_lines_done[2] = 1;
	}
	else if (line[1] != NULL && line[2] == NULL && wall_direction == 3 
		&& parsing->six_lines_done[3] == 0)
	{
		parsing->wall_texture_fds[3] = open(line[1], O_RDONLY);
		if (parsing->wall_texture_fds[3] < 0)
			return (write(1, "Error\nThere is no texture with this name\n", 41)
				, 1);
		parsing->six_lines_done[3] = 1;
	}
	else
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}

int	read_wall_texture(int wall_direction, char **line, t_parsing *parsing)
{
	if (line[1] != NULL && line[2] == NULL && wall_direction == 0 
		&& parsing->six_lines_done[0] == 0)
	{
		parsing->wall_texture_fds[0] = open(line[1], O_RDONLY);
		if (parsing->wall_texture_fds[0] < 0)
			return (write(1, "Error\nThere is no texture with this name\n", 41)
				, 1);
		parsing->six_lines_done[0] = 1;
	}
	else if (line[1] != NULL && line[2] == NULL && wall_direction == 1 
		&& parsing->six_lines_done[1] == 0)
	{
		parsing->wall_texture_fds[1] = open(line[1], O_RDONLY);
		if (parsing->wall_texture_fds[1] < 0)
			return (write(1, "Error\nThere is no texture with this name\n", 41)
				, 1);
		parsing->six_lines_done[1] = 1;
	}
	else
	{
		if (read_wall_texture_block_2(wall_direction, line, parsing) == 1)
			return (1);
	}
	return (0);
}

int	save_colors(int line_type, char **line, t_parsing *parsing)
{
	int		i;
	int		j;
	char	num_type;
	int		got_a_num;
	int		k;

	if (line[1] == NULL)
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	i = 0;
	j = 1;
	num_type = 'r';
	got_a_num = 0;
	k = line_type - 4;
	if ((line_type == 4 && parsing->six_lines_done[4] == 0) 
		|| (line_type == 5 && parsing->six_lines_done[5] == 0))
	{
		while (line[j] != NULL)
		{
			if (got_a_num == 0 && !(line[j][i] >= '0' && line[j][i] <= '9'))
				return (write(1, "wrong RGB input\n", 16), 1);
			else if (!(line[j][i] >= '0' && line[j][i] <= '9') 
				&& line[j][i] != ',' && line[j][i] != '\0')
				return (write(1, "wrong RGB input\n", 16), 1);
			else if (line[j][i] == '\0')
			{
				j++;
				i = 0;
				continue ;
			}
			else if (line[j][i] == ',')
			{
				if (num_type == 'r')
					num_type = 'g';
				else if (num_type == 'g')
					num_type = 'b';
				else if (num_type == 'b')
					return (write(1, "wrong RGB input\n", 16), 1);
			}
			if (line[j][i] >= '0' && line[j][i] <= '9' && num_type == 'r')
			{
				parsing->r[0 + k] = line[j][i] - '0' + parsing->r[0 + k] * 10;
				got_a_num = 1;
			}
			else if (line[j][i] >= '0' && line[j][i] <= '9' && num_type == 'g')
			{
				parsing->g[0 + k] = line[j][i] - '0' + parsing->g[0 + k] * 10;
				got_a_num = 2;
			}
			else if (line[j][i] >= '0' && line[j][i] <= '9' && num_type == 'b')
			{
				parsing->b[0 + k] = line[j][i] - '0' + parsing->b[0 + k] * 10;
				got_a_num = 3;
			}
			i++;
		}
		if (got_a_num != 3)
			return (write(1, "wrong RGB input\n", 16), 1);
		parsing->six_lines_done[4 + k] = 1;
	}
	else 
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}

int	load_textures_and_colors(t_linked_list_map	*linked_list_map, t_parsing *parsing)
{
	// int					i;
	t_linked_list_map	*temp_map;
	char				**line;

	six_lines_done_and_RGB_init(parsing);
	temp_map = linked_list_map;
	// printf("-----------------------------------------\n");
	// print_linked_list(temp_map);
	parsing->main_map_row_num = 0;
	while ((parsing->six_lines_done[0] == 0 || parsing->six_lines_done[1] == 0
		|| parsing->six_lines_done[2] == 0 || parsing->six_lines_done[3] == 0
		|| parsing->six_lines_done[4] == 0 || parsing->six_lines_done[5] == 0)
		&& temp_map != NULL)
	{
		// printf("11111111%s\n", temp_map->row);
		line = ft_split(temp_map->row, ' ');
		if (line[0] == NULL)
			line[0] = NULL;
		else if (line[0][0] == 'S' && line[0][1] == 'O' && line[0][2] == '\0')
		{
			if (read_wall_texture(0, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else if (line[0][0] == 'N' && line[0][1] == 'O' && line[0][2] == '\0')
		{
			if (read_wall_texture(1, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else if (line[0][0] == 'E' && line[0][1] == 'A' && line[0][2] == '\0')
		{
			if (read_wall_texture(2, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else if (line[0][0] == 'W' && line[0][1] == 'E' && line[0][2] == '\0')
		{
			if (read_wall_texture(3, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else if (line[0][0] == 'F' && line[0][1] == '\0')
		{
			if (save_colors(4, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else if (line[0][0] == 'C' && line[0][1] == '\0')
		{
			if (save_colors(5, line, parsing) == 1)
				return (free_double_pointer(line), 1);
		}
		else
			return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
		temp_map = temp_map->next;
		parsing->main_map_row_num++;
		free_double_pointer(line);
	}
	if (temp_map == NULL)
		return (write(1, "Error\nWrite the first 6 lines properly\n", 39), 1);
	return (0);
}

int	check_RGB_and_conv(t_parsing *parsing)
{
	if (parsing->r[0] < 0 || parsing->r[0] > 255 || 
		parsing->r[1] < 0 || parsing->r[1] > 255 || 
		parsing->g[0] < 0 || parsing->g[0] > 255 ||
		parsing->g[1] < 0 || parsing->g[1] > 255 ||
		parsing->b[0] < 0 || parsing->b[0] > 255 ||
		parsing->b[1] < 0 || parsing->b[1] > 255)
		return (1);
	parsing->rgb[0] = (parsing->r[0] << 16) + (parsing->g[0] << 8) + parsing->b[0];
	parsing->rgb[1] = (parsing->r[1] << 16) + (parsing->g[1] << 8) + parsing->b[1];
	// printf("%X, %X\n", parsing->rgb[0], parsing->rgb[1]);
	return (0);
}

void	parsing(char *file_name, t_map *map)
{
	int					fd;
	t_linked_list_map	*linked_list_map;
	t_parsing			*parsing;

	if (check_extension(file_name) == 0)
	{
		write(1, "Error\nWrong file extension\n", 27);
		exit(1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nThere is no file with this name\n", 38);
		exit (1);
	}
	linked_list_map = NULL;
	linked_list_map = building_map(linked_list_map, fd);
	close(fd);
	linked_list_map = trim_map(linked_list_map);
	parsing = malloc(sizeof(t_parsing));
	if (parsing == NULL)
		exit (1);
	if (load_textures_and_colors(linked_list_map, parsing) == 1)
	{
		free_map(linked_list_map);
		free(parsing);
		exit (1);
	}
	map->map = NULL;
	// printf("%d\n", parsing->main_map_row_num);
	map->map = conv_two_d_map(linked_list_map, map->map, parsing->main_map_row_num);
	free_map(linked_list_map);
	if (error(map->map) == 'N')
	{
		free_list_str(map->map);
		free(parsing);
		exit (1);
	}
	if (check_RGB_and_conv(parsing) == 1)
	{
		free_list_str(map->map);
		free(parsing);
		exit (1);
	}
	// printf("%d, %d, %d\n%d, %d, %d\n", parsing->r[0], parsing->g[0], parsing->b[0], parsing->r[1], parsing->g[1], parsing->b[1]);
	printing(map->map);
	map->rgb[0] = parsing->rgb[0];
	map->rgb[1] = parsing->rgb[1];
	// free_double_pointer(map->map);
	// free(parsing);
}

// int	main(int argc, char **argv)
// {
// 	t_map	map;

// 	if (argc != 2)
// 		return (1);
// 	parsing(argv[1], &map);
// 	// data.mlx_ptr = mlx_init();
// 	// if (data.mlx_ptr == NULL)
// 	// {
// 	// 	free_list_str(data.two_d_map);
// 	// 	return (0);
// 	// }
// 	// data.count = 0;
// 	// put_images(&data);
// 	// create_window(&data);
// 	// put_images_on_window(data.two_d_map, data);
// 	// data.steps = 0;
// }
