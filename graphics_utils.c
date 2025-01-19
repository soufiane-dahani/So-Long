/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:28 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/19 10:19:45 by sodahani         ###   ########.fr       */
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

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	number_of_c(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

int	number_of_e(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'E')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}
