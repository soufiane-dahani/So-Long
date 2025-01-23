/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:34:27 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/23 17:15:47 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map_lines(t_parse_vars *vars)
{
	vars->line = get_next_line(vars->fd);
	if (!vars->line)
	{
		free(vars->map);
		ft_printf("Error\n");
		exit(1);
	}
	while (vars->line != NULL)
	{
		if (!process_map_line(vars))
			return (NULL);
		vars->line = get_next_line(vars->fd);
	}
	close(vars->fd);
	vars->map[vars->rows] = NULL;
	return (vars->map);
}

size_t	get_row_length(char *row)
{
	size_t	len;

	len = 0;
	while (row[len] && row[len] != '\n')
		len++;
	return (len);
}

int	check_horizontal_walls(char **map, int row_count, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (map[0][i] != '1' || map[row_count - 1][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_vertical_walls(char **map, int row_count, int len)
{
	int	i;

	i = 0;
	while (i < row_count)
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}
