/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:30:22 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/12 18:33:47 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**allocate_initial_map(int capacity)
{
	char	**map;

	map = malloc(sizeof(char *) * capacity);
	if (!map)
		return (NULL);
	return (map);
}

char	**resize_map(char **map, int rows, int new_capacity)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * new_capacity);
	if (!new_map)
	{
		free_string_array(map);
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

char	**handle_line(char **map, char *line, int *rows, int fd)
{
	map[*rows] = ft_strdup(line);
	if (!map[*rows])
	{
		free_string_array(map);
		free(line);
		close(fd);
		return (NULL);
	}
	(*rows)++;
	return (map);
}

int	init_map_vars(t_parse_vars *vars, const char *file_path)
{
	vars->capacity = 16;
	vars->rows = 0;
	vars->map = allocate_initial_map(vars->capacity);
	if (!vars->map)
		return (0);
	vars->fd = open(file_path, O_RDONLY);
	if (vars->fd < 0)
	{
		free(vars->map);
		return (0);
	}
	return (1);
}

int	process_map_line(t_parse_vars *vars)
{
	if (vars->rows >= vars->capacity - 1)
	{
		vars->capacity *= 2;
		vars->map = resize_map(vars->map, vars->rows, vars->capacity);
		if (!vars->map)
			return (0);
	}
	vars->map = handle_line(vars->map, vars->line, &vars->rows, vars->fd);
	if (!vars->map)
		return (0);
	free(vars->line);
	return (1);
}
