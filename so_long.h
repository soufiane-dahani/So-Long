/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:31 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/16 11:09:05 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"
# include <stdio.h>

typedef struct s_map_info
{
	int			rows;
	int			cols;
	int			player[2];
	int			**visited;
}				t_map_info;

typedef struct s_parse_vars
{
	int			capacity;
	int			rows;
	char		**map;
	int			fd;
	char		*line;
}				t_parse_vars;

typedef struct s_check_vars
{
	int			i;
	int			j;
	int			p;
	int			e;
	int			c;
}				t_check_vars;

typedef struct s_images
{
	void		*wall;
	void		*floor;
	void		*collectible;
	void		*exit;
	void		*player;
}				t_images;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	char		**map;
	int			rows;
	int			cols;
	int			tile_size;
	int			collectibles;
	int			collected;
	int			moves;
	int			player_row;
	int			player_col;
	t_images	*images;
}				t_game;

typedef struct s_move
{
	int	row;
	int	col;
}	t_move;

char			**parse_map(const char *file_path, int *row_count);
void			free_string_array(char **arr);
int				search_ber(const char *file_path);
char			**parse_map(const char *file_path, int *row_count);
int				check_map_characters(char **map, int row_count);
int				validate_map_shape(char **map, int row_count);
int				ensure_the_map_is_surrounded_by_walls(char **map,
					int row_count);
void			free_visited(int **visited, int rows);
int				count_and_check(char **map, t_map_info *info, int *reachable);
int				init_visited_and_player(char **map, t_map_info *info);
void			flood_fill(char **map, t_map_info *info, int row, int col);
int				validate_path(char **map, int row_count);
int				allocate_visited(t_map_info *info, int i);
void			check_player_position(char **map, t_map_info *info, int i,
					int j);
void			init_counters(int *total, int *reachable);
int				check_char(char charr, int *p, int *e, int *c);
char			**allocate_initial_map(int capacity);
char			**resize_map(char **map, int rows, int new_capacity);
char			**handle_line(char **map, char *line, int *rows, int fd);
int				init_map_vars(t_parse_vars *vars, const char *file_path);
int				process_map_line(t_parse_vars *vars);
char			**read_map_lines(t_parse_vars *vars);
size_t			get_row_length(char *row);
int				check_horizontal_walls(char **map, int row_count, int len);
int				check_vertical_walls(char **map, int row_count, int len);
void			error_exit(const char *message);
void			init_window(t_game *game, int rows, int cols, int tile_size);
void			free_img(void *mlx, t_images *images);
void			render_map(t_game *game);
int				handle_keypress(int key, t_game *game);
int				handle_close(t_game *game);
void			cleanup_game(t_game *game);
t_images		*load_images(void *mlx, int tile_size);
void			player_postion_move(char **map, int *new_col, int *new_row);
int				number_of_c(char **map);
int				number_of_e(char **map);
int				is_valid_move(t_game *game, t_move new_pos);
void			update_position(t_game *game, t_move old_pos, t_move new_pos);
void			move_player(t_game *game, t_move old_pos, t_move new_pos);
void			move_to_exit(t_game *game, t_move old_pos, t_move new_pos);
t_move			get_new_position(t_move curr_pos, int key);

#endif