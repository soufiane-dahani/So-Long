/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_maloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:27:18 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/23 10:39:56 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	images->exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &tile_size,
			&tile_size);
	if (!load_player_frames(mlx, images, tile_size) || !validate_images(mlx,
			images) || !load_collectible_frames(mlx, images, tile_size)
		|| !load_enemy_frames(mlx, images, tile_size))
		return (NULL);
	return (images);
}

void	initialize_player_paths(char **paths)
{
	paths[0] = "textures/1.xpm";
	paths[1] = "textures/2.xpm";
	paths[2] = "textures/3.xpm";
	paths[3] = "textures/4.xpm";
	paths[4] = "textures/5.xpm";
	paths[5] = "textures/6.xpm";
}
