/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:31 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:01:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef so_long_H
# define so_long_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <stdio.h>
# include "mlx.h"



typedef struct s_map {
    char **grid;
    int width;
    int height;
    int player_x;
    int player_y;
} t_map;

char **parse_map(const char *file_path, int *row_count);
void	free_string_array(char **arr);
int search_ber(const char *file_path);
char **parse_map(const char *file_path, int *row_count);
int check_map_characters(char **map, int row_count);
int validate_map_shape(char **map, int row_count);
int	ensure_the_map_is_surrounded_by_walls(char **map, int row_count);
void	free_visited(int **visited, int rows);
int count_and_check(char **map, int **visited, int rows, int cols, int *reachable);
int	initialize_visited_and_player(char **map, int **visited,
	int rows, int cols, int *player);
void	flood_fill(char **map, int **visited, int row, int col, int rows, int cols);
int	validate_path(char **map, int row_count);

#endif