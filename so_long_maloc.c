/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_maloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:05:10 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/07 21:23:07 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_list *create_node(void *address)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->address = address;
    new_node->next = NULL;
    return new_node;
}

t_list *add_node(t_list *head, void *address)
{
    t_list *new_node = create_node(address);
    if (!new_node)
        return head;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        t_list *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }

    return head;
}


void *ft_malloc(t_list **head, size_t size)
{
    void *allocated_memory = malloc(size);
    if (!allocated_memory)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    *head = add_node(*head, allocated_memory);

    return allocated_memory;
}

void free_list(t_list *head)
{
    t_list *temp;
    while (head)
    {
        temp = head;
        free(head->address);
        head = head->next;
        free(temp);
    }
}
t_data *init_data(t_list **head)
{

    t_data *data = ft_malloc(head, sizeof(t_data));
    if (!data)
    {
        perror("Failed to allocate memory for t_data");
        return (NULL);
    }

  
    data->mlx = NULL;
    data->win = NULL;
    data->map = NULL;
    data->map_width = 0;
    data->map_height = 0;
    data->player_x = 0;
    data->player_y = 0;
    data->collectibles = 0;
    data->collected = 0;
    data->moves = 0;

    return (data);
}

