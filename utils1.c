/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:37:53 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/23 10:10:15 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_intlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	tmp;
	int		len;
	char	*str;

	tmp = n;
	len = ft_intlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		tmp = -tmp;
	}
	while (tmp > 0)
	{
		str[--len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (str);
}

void	render_player(t_game *game)
{
	int	player_row;
	int	player_col;
	int	row;
	int	col;

	row = 0;
	player_row = game->player_row;
	player_col = game->player_col;
	player_postion_move(game->map, &player_col, &player_row);
	put_image(game, game->images->player[game->player_frame], player_col,
		player_row);
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'C')
				put_image(game, game->images->collectible[game->c_frame], col,
					row);
			if (game->map[row][col] == 'F')
				put_image(game, game->images->enemy[game->e_frame], col, row);
			col++;
		}
		row++;
	}
}

int	game_loop(void *param)
{
	t_game	*game;
	int		i;

	i = 0;
	game = (t_game *)param;
	if (!game || !game->images)
		return (1);
	game->player_frame = (game->player_frame + 1) % 6;
	game->c_frame = (game->c_frame + 1) % 6;
	game->e_frame = (game->e_frame + 1) % 6;
	render_player(game);
	while (i < __INT_MAX__ / 7)
		i++;
	return (0);
}

int	init_game_struct(t_game *game, char *map_path, int *row_count)
{
	ft_memset(game, 0, sizeof(t_game));
	game->tile_size = 40;
	game->collected = 0;
	game->moves = 0;
	game->collectibles = 0;
	game->map = parse_map(map_path, row_count);
	if (!game->map)
		return (1);
	game->rows = *row_count;
	game->cols = ft_strlen(game->map[0]);
	return (0);
}
