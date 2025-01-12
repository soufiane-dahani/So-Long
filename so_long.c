/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:01:28 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>







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
