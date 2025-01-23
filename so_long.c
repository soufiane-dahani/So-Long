/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/21 18:03:03 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_map_requirements(t_game *game, int row_count)
{
	if (check_map_characters(game->map, row_count)
		|| validate_map_shape(game->map, row_count)
		|| ensure_the_map_is_surrounded_by_walls(game->map, row_count)
		|| validate_path(game->map, row_count))
		return (1);
	return (0);
}

static int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->images = load_images(game->mlx, game->tile_size);
	if (!game->images)
		return (1);
	game->win = mlx_new_window(game->mlx, (game->cols - 1) * game->tile_size,
			(game->rows) * game->tile_size, "So Long");
	if (!game->win)
		return (1);
	return (0);
}

static void	setup_mlx_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, handle_close, game);
}

static int	handle_init_errors(t_game *game, int error_type)
{
	if (error_type == 1)
		write(STDERR_FILENO, "Error: \nInvalid arguments\n", 24);
	else if (error_type == 2)
		write(STDERR_FILENO, "Error: \nFailed to parse map\n", 26);
	else if (error_type == 3)
	{
		cleanup_game(game);
		write(STDERR_FILENO, "Error: \nInvalid map\n", 20);
	}
	else if (error_type == 4)
	{
		cleanup_game(game);
		write(STDERR_FILENO, "Error: \nMLX initialization failed\n", 31);
	}
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	int		row_count;

	if (argc != 2)
		return (handle_init_errors(&game, 1));
	if (init_game_struct(&game, argv[1], &row_count))
		return (handle_init_errors(&game, 2));
	if (validate_map_requirements(&game, row_count))
		return (handle_init_errors(&game, 3));
	if (init_mlx_components(&game))
		return (handle_init_errors(&game, 4));
	render_map(&game);
	setup_mlx_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
