/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/08 12:33:30 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_map_boundary(char **map, int width, int height)
{
    int i;

    i = 0;
    while (i < width)
    {
        if (map[0][i] != '1' || map[height - 1][i] != '1')
            return (0);
        i++;
    }
    i = 0;
    while (i < height)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}
static int	validate_map_elements(char **map, int height,
				int *player, int *collect, int *exit)
{
    int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (!ft_strchr(VALID_CHARS, map[y][x]))
				return (0);
			if (map[y][x] == 'P')
				(*player)++;
			if (map[y][x] == 'C')
				(*collect)++;
			if (map[y][x] == 'E')
				(*exit)++;
			x++;
		}
		y++;
	}
	return (1);
                    
}
static char	**allocate_map(list **lines, int height, t_list **head)
{
    char **map;
    int i;

    map = ft_malloc(head, sizeof(char *) * (height + 1));
    if (!map)
        return (NULL);
    i = 0;
    while (*lines)
    {
        map[i] = ft_strdupm((char *)(*lines)->content, head);
        *lines = (*lines)->next;
        i++;
    }
    map[i] = NULL;
    return (map);
}


static int	validate_loaded_map(char **map, int map_height, t_data *data)
{
	int	player;
	int	collect;
	int	exit;

	player = 0;
	collect = 0;
	exit = 0;
	if (!validate_map_boundary(map, ft_strlen(map[0]), map_height))
		return (0);
	if (!validate_map_elements(map, map_height, &player, &collect, &exit))
		return (0);
	if (player != 1 || collect < 1 || exit < 1)
		return (0);
	return (1);
}

char	**load_map(t_list **head, const char *filename, t_data *data)
{
	int		fd;
	t_list	*lines;
	char	*line;
	char	**map;
	int		map_height;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening map file\n"), NULL);
	while ((line = get_next_line(fd)))
		ft_lstadd_back(&lines, ft_lstnew(line, head));
	close(fd);
	if (!lines)
		return (NULL);
	map_height = ft_lstsize(lines);
	map = allocate_map(&lines, map_height, head);
	if (!map || !validate_loaded_map(map, map_height, data))
    {
        free_list(*head);
		return (ft_printf("Error: Invalid map\n"), NULL);
    }
	data->map = map;
	data->map_height = map_height;
	data->map_width = ft_strlen(map[0]);
	return (map);
}
