/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/10 12:35:18 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	ensure_the_map_is_surrounded_by_walls(char **map, int row_count)
{
	int	i;
	int	len;

	i = 0;
	if (!map || row_count <= 0)
		return (1);
	len = 0;
	while (map[0][len] && map[0][len] != '\n')
		len++;
	for (i = 0; i < len; i++)
	{
		if (map[0][i] != '1')
			return (1);
		if (map[row_count - 1][i] != '1')
			return (1);
	}
	for (i = 0; i < row_count; i++)
	{
		if (map[i][0] != '1')
			return (1);
		if (map[i][len - 1] != '1')
			return (1);
	}
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
	free_string_array(map);
	return (EXIT_SUCCESS);
}