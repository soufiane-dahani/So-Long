/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:31 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/08 12:37:25 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef so_long_H
# define so_long_H

# include "ft_printf.h"
# include "get_next_line.h"

# include <stdio.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>



typedef struct s_list
{
    void            *address;
    struct s_list   *next;
} t_list;


typedef struct s_data
{
    void    *mlx;         
    void    *win;          
    char    **map; 
    int     map_width;
    int     map_height;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     collected; 
    int     moves;       
}   t_data;

typedef struct s_listt
{
	void			*content;
	struct s_listt	*next;
}			list;

#define VALID_CHARS "01PCE"

void free_list(t_list *head);
void	ft_lstadd_back(list **alst, list *new);
list	*ft_lstnew(void *content, t_list **head);
int	ft_lstsize(list *lst);
t_list *create_node(void *address);
t_list *add_node(t_list *head, void *address);
void *ft_malloc(t_list **head, size_t size);
t_data *init_data(t_list **head);
char **load_map(t_list **head, const char *filename, t_data *data);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdupm(const char *s1, t_list **head);


#endif