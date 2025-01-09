/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:37:34 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/09 22:45:45 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>

void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	search_ber(const char *file_path)
{
	int	i;

	i = ft_strlen(file_path);
	i = i - 4;
	if (file_path[i] == '.')
	{
		i++;
		if (file_path[i] == 'b')
		{
			i++;
			if (file_path[i] == 'e')
			{
				i++;
				if (file_path[i] == 'r')
					return (1);
			}
		}
	}
	return (0);
}

char	**parse_map(const char *file_path, int *row_count)
{
	int		fd;
	char	**map;
	char	*line;
	int		rows;
	int		capacity;
	char	**new_map;

	map = NULL;
	rows = 0;
	capacity = 1;
	if (!search_ber(file_path))
	{
		write(STDERR_FILENO, "Error should be .ber", 20);
		exit(EXIT_FAILURE);
	}
	map = malloc(sizeof(char *) * capacity);
	if (!map)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		free(map);
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (rows >= capacity)
		{
			capacity *= 2;
			new_map = malloc(sizeof(char *) * capacity);
			if (!new_map)
			{
				perror("Error reallocating memory");
				free_string_array(map);
				exit(EXIT_FAILURE);
			}
			for (int i = 0; i < rows; i++)
			{
				new_map[i] = map[i];
			}
			free(map);
			map = new_map;
		}
		map[rows] = ft_strdup(line);
		if (!map[rows])
		{
			perror("Error duplicating line");
			free_string_array(map);
			exit(EXIT_FAILURE);
		}
		free(line);
		rows++;
	}
	close(fd);
	map[rows] = NULL;
	*row_count = rows;
	return (map);
}

int	check_map_characters(char **map, int row_count)
{
	int	i;
	int	j;
	int	p;
	int	e;
	int	c;

	i = 0;
	p = 0;
	e = 0;
	c = 0;
	while (i < row_count)
	{
		j = 0;
		while (map[i][j] != '\n')
		{
			if (map[i][j] == 'P')
				p++;
			else if (map[i][j] == 'E')
				e++;
			else if (map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	if (p != 1 || e != 1 || c <= 0)
		return (1);
	return (0);
}

int	validate_map_shape(char **map, int row_count)
{
	int	i;
	int	first_row_length;
	int	current_row_length;

	if (row_count == 0 || !map)
		return (1);
	first_row_length = 0;
	while (map[0][first_row_length] != '\0')
		first_row_length++;
	i = 1;
	while (i < row_count)
	{
		current_row_length = 0;
		while (map[i][current_row_length] != '\0')
			current_row_length++;
		if (current_row_length != first_row_length)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		row_count;
	char	**map;

	row_count = 0;
	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Invalid arguments\n", 25);
		return (EXIT_FAILURE);
	}
	map = parse_map(argv[1], &row_count);
	if (!map)
	{
		write(STDERR_FILENO, "Error: Failed to parse map\n", 27);
		return (EXIT_FAILURE);
	}
	if (check_map_characters(map, row_count))
	{
		write(STDERR_FILENO, "Error: char in map\n", 19);
		return (EXIT_FAILURE);
	}
	free_string_array(map);
	return (EXIT_SUCCESS);
}
