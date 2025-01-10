/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:09:03 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/10 11:28:20 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int search_ber(const char *file_path)
{
    size_t len;

    if (!file_path)
        return (0);
    len = ft_strlen(file_path);
    if (len < 4)
        return (0);
    return (file_path[len - 4] == '.' &&
            file_path[len - 3] == 'b' &&
            file_path[len - 2] == 'e' &&
            file_path[len - 1] == 'r');
}

char **parse_map(const char *file_path, int *row_count)
{
    int     fd;
    char    **map;
    char    *line;
    int     rows;
    int     capacity;
    char    **new_map;

    if (!file_path || !row_count)
        return (NULL);
    
    if (!search_ber(file_path))
    {
        write(STDERR_FILENO, "Error: File should be .ber\n", 26);
        return (NULL);
    }

    capacity = 16;
    rows = 0;
    map = malloc(sizeof(char *) * capacity);
    if (!map)
        return (NULL);

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        free(map);
        return (NULL);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        if (rows >= capacity - 1)
        {
            capacity *= 2;
            new_map = malloc(sizeof(char *) * capacity);
            if (!new_map)
            {
                free_string_array(map);
                free(line);
                close(fd);
                return (NULL);
            }
            for (int i = 0; i < rows; i++)
                new_map[i] = map[i];
            free(map);
            map = new_map;
        }
        map[rows] = ft_strdup(line);
        if (!map[rows])
        {
            free_string_array(map);
            free(line);
            close(fd);
            return (NULL);
        }
        free(line);
        rows++;
    }
    close(fd);
    map[rows] = NULL;
    *row_count = rows;
    return (map);
}

int check_map_characters(char **map, int row_count)
{
    int i;
    int j;
    int p;
    int e;
    int c;

    if (!map || row_count <= 0)
        return (1);

    p = 0;
    e = 0;
    c = 0;
    
    for (i = 0; i < row_count; i++)
    {
        if (!map[i])
            return (1);
            
        for (j = 0; map[i][j] != '\0' && map[i][j] != '\n'; j++)
        {
            if (map[i][j] == 'P')
                p++;
            else if (map[i][j] == 'E')
                e++;
            else if (map[i][j] == 'C')
                c++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (1);
        }
    }
    return (p != 1 || e != 1 || c <= 0);
}

int validate_map_shape(char **map, int row_count)
{
    int i;
    size_t first_row_length;
    size_t current_row_length;

    if (row_count <= 0 || !map || !map[0])
        return (1);

    first_row_length = 0;
    while (map[0][first_row_length] && map[0][first_row_length] != '\n')
        first_row_length++;

    for (i = 1; i < row_count; i++)
    {
        if (!map[i])
            return (1);
            
        current_row_length = 0;
        while (map[i][current_row_length] && map[i][current_row_length] != '\n')
            current_row_length++;

        if (current_row_length != first_row_length)
            return (1);
    }
    return (0);
}
