/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:21:47 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	allocate_visited(t_map_info *info, int i)
{
	info->visited[i] = malloc(sizeof(int) * info->cols);
	if (!info->visited[i])
	{
		free_visited(info->visited, i);
		return (1);
	}
	return (0);
}

void	check_player_position(char **map, t_map_info *info, int i, int j)
{
	if (map[i][j] == 'P')
	{
		info->player[0] = i;
		info->player[1] = j;
	}
}

void	init_counters(int *total, int *reachable)
{
	total[0] = 0;
	total[1] = 0;
	reachable[0] = 0;
	reachable[1] = 0;
}

int	count_and_check(char **map, t_map_info *info, int *reachable)
{
	int	i;
	int	j;
	int	total[2];

	init_counters(total, reachable);
	i = 0;
	while (i < info->rows)
	{
		j = 0;
		while (j < info->cols)
		{
			if (map[i][j] == 'C')
				total[0]++;
			else if (map[i][j] == 'E')
				total[1]++;
			if (info->visited[i][j] && map[i][j] == 'C')
				reachable[0]++;
			if (info->visited[i][j] && map[i][j] == 'E')
				reachable[1]++;
			j++;
		}
		i++;
	}
	return (!(reachable[0] == total[0] && reachable[1] == total[1]));
}

int	validate_path(char **map, int row_count)
{
	t_map_info	info;
	int			reachable[2];

	info.rows = row_count;
	info.cols = ft_strlen(map[0]);
	info.visited = malloc(sizeof(int *) * info.rows);
	if (!info.visited)
		return (1);
	if (init_visited_and_player(map, &info))
		return (1);
	flood_fill(map, &info, info.player[0], info.player[1]);
	if (count_and_check(map, &info, reachable))
	{
		free_visited(info.visited, info.rows);
		return (1);
	}
	free_visited(info.visited, info.rows);
	return (0);
}
