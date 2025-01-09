/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:52:22 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/09 19:19:13 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_fill_line_buffer(int fd, char *remains, char *buffer)
{
	ssize_t	nbytes;
	char	*tmp;

	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(remains);
			return (NULL);
		}
		else if (nbytes == 0)
			break ;
		buffer[nbytes] = 0;
		if (!remains)
			remains = ft_strdup("");
		tmp = remains;
		remains = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (remains);
}

static char	*ft_separate_lines(char *line_buffer)
{
	char	*remain_lines;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[i + 1] == 0)
		return (NULL);
	remain_lines = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!remain_lines)
	{
		free(remain_lines);
		remain_lines = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (remain_lines);
}

char	*get_next_line(int fd)
{
	static char	*remains;
	char		*buffer;
	char		*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(remains);
		buffer = NULL;
		remains = NULL;
		return (NULL);
	}
	line = ft_fill_line_buffer(fd, remains, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remains = ft_separate_lines(line);
	return (line);
}
