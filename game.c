/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:44:28 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/21 18:10:14 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	cleanup_player_images(void *mlx, t_images *images)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (images->player[i])
			mlx_destroy_image(mlx, images->player[i]);
		images->player[i] = NULL;
		i++;
	}
}

static void	cleanup_collectible_images(void *mlx, t_images *images)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (images->collectible[i])
			mlx_destroy_image(mlx, images->collectible[i]);
		images->collectible[i] = NULL;
		i++;
	}
}

static void	cleanup_enemy_images(void *mlx, t_images *images)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (images->enemy[i])
			mlx_destroy_image(mlx, images->enemy[i]);
		images->enemy[i] = NULL;
		i++;
	}
}

static void	cleanup_static_images(void *mlx, t_images *images)
{
	if (images->wall)
		mlx_destroy_image(mlx, images->wall);
	images->wall = NULL;
	if (images->exit)
		mlx_destroy_image(mlx, images->exit);
	images->exit = NULL;
	if (images->floor)
		mlx_destroy_image(mlx, images->floor);
	images->floor = NULL;
}

void	cleanup_images(void *mlx, t_images *images)
{
	if (!mlx || !images)
		return ;
	cleanup_player_images(mlx, images);
	cleanup_collectible_images(mlx, images);
	cleanup_enemy_images(mlx, images);
	cleanup_static_images(mlx, images);
	free(images);
}
