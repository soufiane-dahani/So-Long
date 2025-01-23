/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:38 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/23 10:40:40 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

static void	initialize_enemy_paths(char **paths)
{
	paths[0] = "textures/enemy1.xpm";
	paths[1] = "textures/enemy2.xpm";
	paths[2] = "textures/enemy3.xpm";
	paths[3] = "textures/enemy4.xpm";
	paths[4] = "textures/enemy5.xpm";
	paths[5] = "textures/enemy6.xpm";
	paths[6] = "textures/enemy7.xpm";
	paths[7] = "textures/enemy8.xpm";
}

static int	destroy_enemy_images(void *mlx, t_images *images, int count)
{
	while (--count >= 0)
	{
		mlx_destroy_image(mlx, images->enemy[count]);
		images->enemy[count] = NULL;
	}
	return (0);
}

int	load_enemy_frames(void *mlx, t_images *images, int tile_size)
{
	int		i;
	char	*paths[8];

	initialize_enemy_paths(paths);
	i = 0;
	while (i < 8)
	{
		images->enemy[i] = mlx_xpm_file_to_image(mlx, paths[i], &tile_size,
				&tile_size);
		if (!images->enemy[i])
		{
			ft_printf("Error: Failed to load enemy frame: %s\n", paths[i]);
			return (destroy_enemy_images(mlx, images, i));
		}
		i++;
	}
	return (1);
}

static int	destroy_loaded_images(void *mlx, t_images *images, int count)
{
	while (--count >= 0)
	{
		mlx_destroy_image(mlx, images->player[count]);
		images->player[count] = NULL;
	}
	return (0);
}

int	load_player_frames(void *mlx, t_images *images, int tile_size)
{
	int		i;
	char	*paths[6];

	initialize_player_paths(paths);
	i = 0;
	while (i < 6)
	{
		images->player[i] = mlx_xpm_file_to_image(mlx, paths[i], &tile_size,
				&tile_size);
		if (!images->player[i])
		{
			ft_printf("Error: Failed to load player frame: %s\n", paths[i]);
			return (destroy_loaded_images(mlx, images, i));
		}
		i++;
	}
	return (1);
}
