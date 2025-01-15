/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/15 09:51:45 by sodahani         ###   ########.fr       */
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
	if (images->player)
		mlx_destroy_image(mlx, images->player);
	free(images);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->images)
		free_img(game->mlx, game->images);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_string_array(game->map);
}

t_images	*load_images(void *mlx, int tile_size)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	if (!images)
		return (NULL);
	images->wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &tile_size,
			&tile_size);
	images->floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &tile_size,
			&tile_size);
	images->collectible = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm",
			&tile_size, &tile_size);
	images->exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &tile_size,
			&tile_size);
	images->player = mlx_xpm_file_to_image(mlx, "textures/player.xpm",
			&tile_size, &tile_size);
	if (!images->wall || !images->floor || !images->collectible || !images->exit
		|| !images->player)
	{
		free_img(mlx, images);
		return (NULL);
	}
	return (images);
}
