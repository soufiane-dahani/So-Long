/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:01:33 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


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
	int	i;
	int	j;

	i = 0;
	player[0] = -1;
	player[1] = -1;
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
		return (free_visited(visited, rows), 1);
	return (0);
}

void	flood_fill(char **map, int **visited, int row, int col, int rows, int cols)
{
	if (row < 0 || col < 0 || row >= rows || col >= cols)
		return;
	if (visited[row][col] || map[row][col] == '1')
		return;
	visited[row][col] = 1;
	flood_fill(map, visited, row + 1, col, rows, cols);
	flood_fill(map, visited, row - 1, col, rows, cols);
	flood_fill(map, visited, row, col + 1, rows, cols);
	flood_fill(map, visited, row, col - 1, rows, cols);
}

int	count_and_check(char **map, int **visited, int rows, int cols, int *reachable)
{
	int	i;
	int	j;
	int	total[2];

	total[0] = 0;
	total[1] = 0;
	reachable[0] = 0;
	reachable[1] = 0;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'C')
				total[0]++;
			else if (map[i][j] == 'E')
				total[1]++;
			if (visited[i][j] && map[i][j] == 'C')
				reachable[0]++;
			if (visited[i][j] && map[i][j] == 'E')
				reachable[1]++;
			j++;
		}
		i++;
	}
	if (reachable[0] == total[0] && reachable[1] == total[1])
		return (0);
	return (1);
}

int	validate_path(char **map, int row_count)
{
	int		rows;
	int		cols;
	int		**visited;
	int		player[2];
	int		reachable[2];

	rows = row_count;
	cols = ft_strlen(map[0]);
	visited = malloc(sizeof(int *) * rows);
	if (!visited)
		return (1);

	if (initialize_visited_and_player(map, visited, rows, cols, player))
		return (1);
	flood_fill(map, visited, player[0], player[1], rows, cols);
	if (count_and_check(map, visited, rows, cols, reachable))
	{
		free_visited(visited, rows);
		return (1);
	}
	free_visited(visited, rows);
	return (0);
}