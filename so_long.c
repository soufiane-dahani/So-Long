/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/20 11:14:29 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_player_frames(void *mlx, t_images *images, int tile_size)
{
	int	i;

	char *paths[] = {
		"textures/1.xpm", "textures/2.xpm", "textures/3.xpm", "textures/4.xpm",
			"textures/5.xpm", "textures/6.xpm"};
	i = 0;
	while (i < 6)
	{
		images->player[i] = mlx_xpm_file_to_image(mlx, paths[i], &tile_size,
				&tile_size);
		if (!images->player[i])
		{
			ft_printf("Error: Failed to load player frame: %s\n", paths[i]);
			while (--i >= 0)
			{
				mlx_destroy_image(mlx, images->player[i]);
				images->player[i] = NULL;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

void	render_player(t_game *game)
{
	int	player_row;
	int	player_col;

	player_row = game->player_row;
	player_col = game->player_col;
	player_postion_move(game->map, &player_col, &player_row);
	put_image(game, game->images->player[game->player_frame], player_col,
			player_row);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->images)
		return (1);
	game->player_frame = (game->player_frame + 1) % 6;
	render_player(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	int		row_count;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: \nInvalid arguments\n", 24);
		return (EXIT_FAILURE);
	}
	game.tile_size = 40;
	game.collected = 0;
	game.moves = 0;
	game.collectibles = 0;
	game.map = parse_map(argv[1], &row_count);
	if (!game.map)
	{
		write(STDERR_FILENO, "Error: \nFailed to parse map\n", 26);
		return (EXIT_FAILURE);
	}
	game.rows = row_count;
	game.cols = ft_strlen(game.map[0]);
	if (check_map_characters(game.map, row_count) ||
		validate_map_shape(game.map, row_count) ||
		ensure_the_map_is_surrounded_by_walls(game.map, row_count) ||
		validate_path(game.map, row_count))
	{
		cleanup_game(&game);
		write(STDERR_FILENO, "Error: \nInvalid map\n", 20);
		return (EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		cleanup_game(&game);
		write(STDERR_FILENO, "Error: \nFailed to initialize MLX\n", 31);
		return (EXIT_FAILURE);
	}
	game.images = load_images(game.mlx, game.tile_size);
	if (!game.images)
	{
		cleanup_game(&game);
		write(STDERR_FILENO, "Error: \nFailed to load images\n", 28);
		return (EXIT_FAILURE);
	}
	game.win = mlx_new_window(game.mlx, (game.cols - 1) * game.tile_size,
			(game.rows) * game.tile_size, "So Long");
	if (!game.win)
	{
		cleanup_game(&game);
		write(STDERR_FILENO, "Error: \nFailed to create window\n", 30);
		return (EXIT_FAILURE);
	}
	render_map(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, NoEventMask, handle_close, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (EXIT_SUCCESS);
}
