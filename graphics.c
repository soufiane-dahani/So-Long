/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/20 11:27:29 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	init_window(t_game *game, int rows, int cols, int tile_size)
{
	if (!game)
		return ;
	game->tile_size = tile_size;
	game->rows = rows;
	game->cols = cols;
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->win = mlx_new_window(game->mlx,
								cols * tile_size,
								rows * tile_size,
								"So Long!");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_img(void *mlx, t_images *images)
{
	if (!mlx || !images)
		return ;
	if (images->wall)
		mlx_destroy_image(mlx, images->wall);
	if (images->floor)
		mlx_destroy_image(mlx, images->floor);
	if (images->collectible)
		mlx_destroy_image(mlx, images->collectible);
	if (images->exit)
		mlx_destroy_image(mlx, images->exit);
	if (images->enemy)
		mlx_destroy_image(mlx, images->enemy);
	free(images);
}

static void	cleanup_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		game->map[i] = NULL;
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->images)
	{
		cleanup_images(game->mlx, game->images);
		game->images = NULL;
	}
	cleanup_map(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
