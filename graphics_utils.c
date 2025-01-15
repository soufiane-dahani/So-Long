/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:28 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/15 10:34:34 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, void *img, int col, int row)
{
	mlx_put_image_to_window(game->mlx, game->win, img, col * game->tile_size,
		row * game->tile_size);
}

void	render_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (col < game->cols)
		{
			put_image(game, game->images->floor, col, row);
			if (game->map[row][col] == '1')
				put_image(game, game->images->wall, col, row);
			else if (game->map[row][col] == 'C')
				put_image(game, game->images->collectible, col, row);
			else if (game->map[row][col] == 'E')
				put_image(game, game->images->exit, col, row);
			else if (game->map[row][col] == 'P')
				put_image(game, game->images->player, col, row);
			col++;
		}
		row++;
	}
}

int	handle_keypress(int key, t_game *game)
{
	if (key == 65307)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}
