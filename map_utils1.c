/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:07:57 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/14 15:33:47 by sodahani         ###   ########.fr       */
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

int	init_visited_and_player(char **map, t_map_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->player[0] = -1;
	info->player[1] = -1;
	while (i < info->rows)
	{
		if (allocate_visited(info, i))
			return (1);
		j = 0;
		while (j < info->cols)
		{
			info->visited[i][j] = 0;
			check_player_position(map, info, i, j);
			j++;
		}
		i++;
	}
	if (info->player[0] == -1 || info->player[1] == -1)
	{
		free_visited(info->visited, info->rows);
		return (1);
	}
	return (0);
}

void	flood_fill(char **map, t_map_info *info, int row, int col)
{
	if (row < 0 || col < 0 || row >= info->rows || col >= info->cols)
		return ;
	if (info->visited[row][col] || map[row][col] == '1')
		return ;
	info->visited[row][col] = 1;
	flood_fill(map, info, row + 1, col);
	flood_fill(map, info, row - 1, col);
	flood_fill(map, info, row, col + 1);
	flood_fill(map, info, row, col - 1);
}

int	search_ber(const char *file_path)
{
	size_t	len;

	if (!file_path)
		return (0);
	len = ft_strlen(file_path);
	if (len < 4)
		return (0);
	return (file_path[len - 4] == '.' && file_path[len - 3] == 'b'
		&& file_path[len - 2] == 'e' && file_path[len - 1] == 'r');
}

int	check_char(char charr, int *p, int *e, int *c)
{
	if (charr == 'P')
		(*p)++;
	else if (charr == 'E')
		(*e)++;
	else if (charr == 'C')
		(*c)++;
	else if (charr != '0' && charr != '1')
		return (1);
	return (0);
}
