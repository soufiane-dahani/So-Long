/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:38 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/20 11:55:47 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	validate_images(void *mlx, t_images *images)
{
	if (!images->wall || !images->floor || !images->collectible || !images->exit
		|| !images->enemy)
	{
		free_img(mlx, images);
		return (0);
	}
	return (1);
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
	images->enemy = mlx_xpm_file_to_image(mlx, "textures/enemy.xpm", &tile_size,
			&tile_size);
	if (!load_player_frames(mlx, images, tile_size) || !validate_images(mlx,
			images))
		return (NULL);
	return (images);
}
