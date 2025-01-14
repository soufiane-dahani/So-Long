/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/14 12:58:08 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void    free_img(void *mlx, t_images *images) {
    if (!mlx || !images)
        return;
    if (images->wall)
        mlx_destroy_image(mlx, images->wall);
    if (images->floor)
        mlx_destroy_image(mlx, images->floor);
    if (images->collectible)
        mlx_destroy_image(mlx, images->collectible);
    if (images->exit)
        mlx_destroy_image(mlx, images->exit);
    if (images->player)
        mlx_destroy_image(mlx, images->player);
    free(images);
}

void    cleanup_game(t_game *game) {
    if (!game)
        return;
    if (game->images)
        free_img(game->mlx, game->images);
    if (game->win && game->mlx)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx) {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    if (game->map)
        free_string_array(game->map);
}

t_images *load_images(void *mlx, int tile_size) {
    t_images *images;

    images = malloc(sizeof(t_images));
    if (!images)
        return (NULL);
    
    images->wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &tile_size, &tile_size);
    images->floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &tile_size, &tile_size);
    images->collectible = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &tile_size, &tile_size);
    images->exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &tile_size, &tile_size);
    images->player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &tile_size, &tile_size);

    if (!images->wall || !images->floor || !images->collectible || 
        !images->exit || !images->player) {
        free_img(mlx, images);
        return (NULL);
    }
    return (images);
}

void render_map(t_game *game)
{
    int row;
    int col;
    int tile_width = game->tile_size;
    int tile_height = game->tile_size;

    row = 0;
    while (row < game->rows) {
        col = 0;
        while (col < game->cols) {
            mlx_put_image_to_window(game->mlx, game->win, game->images->floor,
                col * tile_width, row * tile_height);
            if (game->map[row][col] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->images->wall,
                    col * tile_width, row * tile_height);
            else if (game->map[row][col] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->images->collectible,
                    col * tile_width, row * tile_height);
            else if (game->map[row][col] == 'E') 
                mlx_put_image_to_window(game->mlx, game->win, game->images->exit,
                    col * tile_width, row * tile_height);
            else if (game->map[row][col] == 'P') 
                mlx_put_image_to_window(game->mlx, game->win, game->images->player,
                    col * tile_width, row * tile_height);
            col++;
        }
        row++;
    }
}


int handle_keypress(int key, t_game *game) {
    if (key == 53)
        cleanup_game(game);
    return (0);
}

int    handle_close(t_game *game) {
    cleanup_game(game);
    exit(EXIT_SUCCESS);
    return (0);
}


int main(int argc, char *argv[]) {
    t_game game;
    int row_count;

    if (argc != 2) {
        write(STDERR_FILENO, "Error: Invalid arguments\n", 24);
        return (EXIT_FAILURE);
    }
    game.tile_size = 32;
    game.collected = 0;
    game.moves = 0;
    game.collectibles = 0;
    game.map = parse_map(argv[1], &row_count);
    if (!game.map) {
        write(STDERR_FILENO, "Error: Failed to parse map\n", 26);
        return (EXIT_FAILURE);
    }

    game.rows = row_count;
    game.cols = ft_strlen(game.map[0]);
    if (check_map_characters(game.map, row_count) ||
        validate_map_shape(game.map, row_count) ||
        ensure_the_map_is_surrounded_by_walls(game.map, row_count) ||
        validate_path(game.map, row_count)) {
        free_string_array(game.map);
        write(STDERR_FILENO, "Error: Invalid map\n", 20);
        return (EXIT_FAILURE);
    }
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.cols * game.tile_size, game.rows * game.tile_size, "So Long and Thanks For All the Fish");
    game.images = load_images(game.mlx, game.tile_size);
    if (!game.images) {
        cleanup_game(&game);
        write(STDERR_FILENO, "Error: Failed to load images\n", 28);
        return (EXIT_FAILURE);
    }
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, handle_close, &game);
    render_map(&game);
    mlx_loop(game.mlx);

    return (EXIT_SUCCESS);
}