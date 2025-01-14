/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:00 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/14 12:17:57 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void    error_exit(const char *message)
{
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}

void    init_window(t_game *game, int rows, int cols, int tile_size) {
    if (!game)
        return;
        
    game->tile_size = tile_size;
    game->rows = rows;
    game->cols = cols;
    
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
        return;
        
    // Create window with the correct dimensions
    game->win = mlx_new_window(game->mlx, 
                              cols * tile_size,
                              rows * tile_size,
                              "So Long!");
                              
    if (!game->win) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        game->mlx = NULL;
    }
}

