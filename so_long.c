/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 19:11:10 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>




int	main(int argc, char *argv[])
{
	void *mlx;
	void *win;
	int		row_count;
	char	**map;
	int tile_size = 32;
    int rows = 10;
    int cols = 10;
    int win_width = cols * tile_size;
    int win_height = rows * tile_size;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Invalid arguments\n", 24);
		return (EXIT_FAILURE);
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, win_width, win_height, "So Long Game");
	
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
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
