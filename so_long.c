/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/15 13:47:15 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void player_postion_move(char **map, int *new_col, int *new_row)
{
    int i = 0;
    int j;
    int len = ft_strlen(map[0]);

    while (i < len)
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == 'P')
            {
                *new_row = i;
                *new_col = j;
                return;
            }
            j++;
        }
        i++;
    }
}


int	handle_keypress(int key, t_game *game)
{
	int	new_row;
	int	new_col;
	int	old_row;
	int	old_col;

	if (!game)
		return (1);
	if (key == 65307)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	player_postion_move(game->map, &new_col, &new_row);
	old_col = new_col;
	old_row = new_row;
	if (key == 119)
		new_row -= 1;
	else if (key == 97)
		new_col -= 1;
	else if (key == 115)
		new_row += 1;
	else if (key == 100)
		new_col += 1;
	if (new_row >= 0 && new_row < game->rows &&
		new_col >= 0 && new_col < game->cols &&
		game->map[new_row][new_col] != '1')
	{
		game->map[old_row][old_col] = '0';
		game->map[new_row][new_col] = 'P';
		game->player_row = new_row;
		game->player_col = new_col;
		game->moves++;
		ft_printf("moves : %d\n", game->moves);
		mlx_clear_window(game->mlx, game->win);
		render_map(game);
	}
	return (0);
}





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
