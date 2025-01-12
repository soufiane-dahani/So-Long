/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:31 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:42:57 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>

typedef struct s_map_info
{
	int		rows;
	int		cols;
	int		player[2];
	int		**visited;
}			t_map_info;

typedef struct s_parse_vars
{
	int		capacity;
	int		rows;
	char	**map;
	int		fd;
	char	*line;
}			t_parse_vars;

typedef struct s_check_vars
{
	int		i;
	int		j;
	int		p;
	int		e;
	int		c;
}			t_check_vars;

char		**parse_map(const char *file_path, int *row_count);
void		free_string_array(char **arr);
int			search_ber(const char *file_path);
char		**parse_map(const char *file_path, int *row_count);
int			check_map_characters(char **map, int row_count);
int			validate_map_shape(char **map, int row_count);
int			ensure_the_map_is_surrounded_by_walls(char **map, int row_count);
void		free_visited(int **visited, int rows);
int			count_and_check(char **map, t_map_info *info, int *reachable);
int			init_visited_and_player(char **map, t_map_info *info);
void		flood_fill(char **map, t_map_info *info, int row, int col);
int			validate_path(char **map, int row_count);
int			allocate_visited(t_map_info *info, int i);
void		check_player_position(char **map, t_map_info *info, int i, int j);
void		init_counters(int *total, int *reachable);
int			check_char(char charr, int *p, int *e, int *c);
char		**allocate_initial_map(int capacity);
char		**resize_map(char **map, int rows, int new_capacity);
char		**handle_line(char **map, char *line, int *rows, int fd);
int			init_map_vars(t_parse_vars *vars, const char *file_path);
int			process_map_line(t_parse_vars *vars);
char		**read_map_lines(t_parse_vars *vars);
size_t		get_row_length(char *row);
int			check_horizontal_walls(char **map, int row_count, int len);
int			check_vertical_walls(char **map, int row_count, int len);

#endif