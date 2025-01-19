/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:05:33 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/19 21:43:13 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_position(t_game *game, t_move old_pos, t_move new_pos)
{
	game->map[old_pos.row][old_pos.col] = '0';
	game->map[new_pos.row][new_pos.col] = 'P';
	game->player_row = new_pos.row;
	game->player_col = new_pos.col;
	if (new_pos.col != old_pos.col || new_pos.row != old_pos.row)
		ft_printf("moves : %d\n", game->moves++);
	mlx_clear_window(game->mlx, game->win);
	render_map(game);
}

void	move_player(t_game *game, t_move old_pos, t_move new_pos)
{
	if (is_valid_move(game, new_pos)
		&& game->map[new_pos.row][new_pos.col] != 'E'
		&& game->map[new_pos.row][new_pos.col] != 'F')
	{
		update_position(game, old_pos, new_pos);
		game->collectibles = number_of_c(game->map);
	}
}

void	move_to_exit(t_game *game, t_move old_pos, t_move new_pos)
{
	if (is_valid_move(game, new_pos) && game->collectibles == 0
	&& game->map[new_pos.row][new_pos.col] != 'F')
	{
		update_position(game, old_pos, new_pos);
		if (number_of_e(game->map) == 0)
		{
			cleanup_game(game);
			exit(0);
		}
	}
}

t_move	get_new_position(t_move curr_pos, int key)
{
	t_move	new_pos;

	new_pos = curr_pos;
	if (key == 119)
		new_pos.row -= 1;
	else if (key == 97)
		new_pos.col -= 1;
	else if (key == 115)
		new_pos.row += 1;
	else if (key == 100)
		new_pos.col += 1;
	return (new_pos);
}

int	handle_keypress(int key, t_game *game)
{
	t_move	old_pos;
	t_move	new_pos;

	if (!game)
		return (1);
	if (key == 65307)
	{
		cleanup_game(game);
		exit(EXIT_SUCCESS);
	}
	player_postion_move(game->map, &old_pos.col, &old_pos.row);
	new_pos = get_new_position(old_pos, key);
	if (new_pos.col != old_pos.col || new_pos.row != old_pos.row)
	{
		move_player(game, old_pos, new_pos);
		move_to_exit(game, old_pos, new_pos);
	}
	return (0);
}
