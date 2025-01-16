/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/16 11:05:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	int		row_count;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Invalid arguments\n", 24);
		return (EXIT_FAILURE);
	}
	game.tile_size = 32;
	game.collected = 0;
	game.moves = 0;
	game.collectibles = 0;
	game.map = parse_map(argv[1], &row_count);
	if (!game.map)
	{
		write(STDERR_FILENO, "Error: Failed to parse map\n", 26);
		return (EXIT_FAILURE);
	}
	game.rows = row_count;
	game.cols = ft_strlen(game.map[0]);
	if (check_map_characters(game.map, row_count) ||
		validate_map_shape(game.map, row_count) ||
		ensure_the_map_is_surrounded_by_walls(game.map, row_count) ||
		validate_path(game.map, row_count))
	{
		free_string_array(game.map);
		write(STDERR_FILENO, "Error: Invalid map\n", 20);
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	game.images = load_images(game.mlx, game.tile_size);
	game.win = mlx_new_window(game.mlx, (game.cols - 1) * game.tile_size,
			(game.rows) * game.tile_size, "So Long");
	if (!game.images)
	{
		cleanup_game(&game);
		write(STDERR_FILENO, "Error: Failed to load images\n", 28);
		return (EXIT_FAILURE);
	}
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
