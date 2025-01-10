/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/10 17:56:52 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

void	free_visited(int **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
int	initialize_visited_and_player(char **map, int **visited,
	int rows, int cols, int *player)
{
    int i;
    int j;
    
    i = 0;
    while (i < rows)
    {
        visited[i] = malloc(sizeof(int) * cols);
        if (!visited[i])
            return (free_visited(visited, i), 1);
        j = 0;
        while (j < cols)
        {
            visited[i][j] = 0;
            if (map[i][j] == 'P')
            {
                player[0] = i;
                player[1] = j;
            }
            j++;
        }
        i++;
    }
    if (player[0] == -1 || player[1] == -1)
        return 1;
    return 0;
}

void	flood_fill(char **map, int **visited, int row, int col, int rows, int cols)
{
    if (row < 0 || col < 0 || row >= rows || col >= cols)
		return ;
    if (visited[row][col] || map[row][col] == '1')
		return ;
    flood_fill(map, visited, row + 1, col, rows, cols);
	flood_fill(map, visited, row - 1, col, rows, cols);
	flood_fill(map, visited, row, col + 1, rows, cols);
	flood_fill(map, visited, row, col - 1, rows, cols);
}

int	validate_path(char **map, int row_count)
{
    int rows;
    int cols;
    int **visited;
    int palayer[2];
    int reachable[2];

    rows = row_count;
    cols = ft_strlen(map[0]);
    visited = malloc = (sizeof(int *) * rows);
    if (!visited)
        return 1;
    palayer[0] = -1;
    palayer[1] = -1;
    if (initialize_visited_and_player(map, visited, rows, cols, player))
		return (free_visited(visited, rows), 1);
    flood_fill(map, visited, player[0], player[1], rows, cols);
    if (count_and_check(map, visited, rows, cols, reachable))
		return (free_visited(visited, rows), 1);
	free_visited(visited, rows);
	return (0);
}




int	main(int argc, char *argv[])
{
	int row_count;
	char **map;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Invalid arguments\n", 24);
		return (EXIT_FAILURE);
	}

	map = parse_map(argv[1], &row_count);
	if (!map)
	{
		write(STDERR_FILENO, "Error: Failed to parse map\n", 26);
		return (EXIT_FAILURE);
	}

	if (check_map_characters(map, row_count))
	{
		write(STDERR_FILENO, "Error: Invalid map characters\n", 29);
		free_string_array(map);
		return (EXIT_FAILURE);
	}

	if (validate_map_shape(map, row_count))
	{
		write(STDERR_FILENO, "Error: Map is not rectangular\n", 29);
		free_string_array(map);
		return (EXIT_FAILURE);
	}
	if (ensure_the_map_is_surrounded_by_walls(map, row_count))
	{
		write(STDERR_FILENO, "Error: ensure_the_map_is_surrounded_by_walls\n",
				44);
		free_string_array(map);
		return (EXIT_FAILURE);
	}
    if (validate_path(map, row_count))
    {
	write(STDERR_FILENO, "Error: Unreachable paths in map\n", 32);
	free_string_array(map);
	return (EXIT_FAILURE);
    }
	free_string_array(map);
	return (EXIT_SUCCESS);
}