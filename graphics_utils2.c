/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:36 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/20 11:26:18 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_postion_move(char **map, int *new_col, int *new_row)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	while (i < len)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				*new_row = i;
				*new_col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	is_valid_move(t_game *game, t_move new_pos)
{
	return (new_pos.row >= 0 && new_pos.row < game->rows && new_pos.col >= 0
		&& new_pos.col < game->cols
		&& game->map[new_pos.row][new_pos.col] != '1');
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	cleanup_images(void *mlx, t_images *images)
{
	int	i;

	if (!mlx || !images)
		return ;
	i = 0;
	while (i < 6)
	{
		if (images->player[i])
			mlx_destroy_image(mlx, images->player[i]);
		images->player[i] = NULL;
		i++;
	}
	if (images->wall)
		mlx_destroy_image(mlx, images->wall);
	images->wall = NULL;
	if (images->collectible)
		mlx_destroy_image(mlx, images->collectible);
	images->collectible = NULL;
	if (images->exit)
		mlx_destroy_image(mlx, images->exit);
	images->exit = NULL;
	if (images->floor)
		mlx_destroy_image(mlx, images->floor);
	images->floor = NULL;
	free(images);
}

void	move_game_over(t_game *game, t_move old_pos, t_move new_pos)
{
	if (!game || !game->map)
		return ;
	if (is_valid_move(game, new_pos)
		&& game->map[new_pos.row][new_pos.col] == 'F')
	{
		update_position(game, old_pos, new_pos);
		ft_printf("Game over\n");
		cleanup_game(game);
		exit(EXIT_FAILURE);
	}
}
