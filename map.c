/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/20 16:22:37 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_map(const char *file_path, int *row_count)
{
	t_parse_vars	vars;

	if (!file_path || !row_count || !search_ber(file_path))
	{
		if (file_path)
			write(STDERR_FILENO, "Error: File should be .ber\n", 26);
		return (NULL);
	}
	if (!init_map_vars(&vars, file_path))
		return (NULL);
	vars.map = read_map_lines(&vars);
	if (!vars.map)
		return (NULL);
	*row_count = vars.rows;
	return (vars.map);
}

int	check_map_characters(char **map, int row_count)
{
	t_check_vars	vars;

	if (!map || row_count <= 0)
		return (1);
	vars.p = 0;
	vars.e = 0;
	vars.c = 0;
	vars.i = 0;
	while (vars.i < row_count)
	{
		if (!map[vars.i])
			return (1);
		vars.j = 0;
		while (map[vars.i][vars.j] != '\0' && map[vars.i][vars.j] != '\n')
		{
			if (check_char(map[vars.i][vars.j], &vars.p, &vars.e, &vars.c))
				return (1);
			vars.j++;
		}
		vars.i++;
	}
	return (vars.p != 1 || vars.e != 1 || vars.c <= 0);
}

int	validate_map_shape(char **map, int row_count)
{
	int		i;
	size_t	first_row_length;
	size_t	current_row_length;

	if (row_count <= 0 || !map || !map[0])
		return (1);
	first_row_length = get_row_length(map[0]);
	if (first_row_length > 48 || row_count > 25)
		return (1);
	i = 1;
	while (i < row_count)
	{
		if (!map[i])
			return (1);
		current_row_length = get_row_length(map[i]);
		if (current_row_length != first_row_length)
			return (1);
		i++;
	}
	return (0);
}

int	ensure_the_map_is_surrounded_by_walls(char **map, int row_count)
{
	int	len;

	if (!map || row_count <= 0)
		return (1);
	len = 0;
	while (map[0][len] && map[0][len] != '\n')
		len++;
	if (check_horizontal_walls(map, row_count, len))
		return (1);
	if (check_vertical_walls(map, row_count, len))
		return (1);
	return (0);
}
