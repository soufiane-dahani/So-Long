/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:36 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/16 11:05:23 by sodahani         ###   ########.fr       */
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
