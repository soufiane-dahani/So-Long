/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/13 11:35:06 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void    error_exit(const char *message)
{
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

void    init_window(t_game *game, int rows, int cols, int tile_size)
{
    game->win_width = cols * tile_size;
    game->win_height = rows * tile_size;

    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Error: MiniLibX initialization failed");

    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "So Long Game");
    if (!game->win)
        error_exit("Error: Window creation failed");
}

