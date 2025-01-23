/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:32 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/23 10:21:59 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	initialize_paths(char **paths)
{
	paths[0] = "textures/collectible8.xpm";
	paths[1] = "textures/collectible9.xpm";
	paths[2] = "textures/collectible10.xpm";
	paths[3] = "textures/collectible11.xpm";
	paths[4] = "textures/collectible12.xpm";
	paths[5] = "textures/collectible13.xpm";
}

static int	destroy_loaded_images(void *mlx, t_images *images, int count)
{
	while (--count >= 0)
	{
		mlx_destroy_image(mlx, images->collectible[count]);
		images->collectible[count] = NULL;
	}
	return (0);
}

int	load_collectible_frames(void *mlx, t_images *images, int tile_size)
{
	int		i;
	char	*paths[6];

	initialize_paths(paths);
	i = 0;
	while (i < 6)
	{
		images->collectible[i] = mlx_xpm_file_to_image(mlx, paths[i],
				&tile_size, &tile_size);
		if (!images->collectible[i])
		{
			ft_printf("Error: Failed to load player frame: %s\n", paths[i]);
			return (destroy_loaded_images(mlx, images, i));
		}
		i++;
	}
	return (1);
}

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

int	validate_images(void *mlx, t_images *images)
{
	if (!images->wall || !images->floor || !images->exit)
	{
		free_img(mlx, images);
		return (0);
	}
	return (1);
}
