/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sodahani <sodahani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:27 by sodahani          #+#    #+#             */
/*   Updated: 2025/01/08 12:33:24 by sodahani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int initialize_miniLibx(t_data *data, t_list *head)
{
    data->mlx = mlx_init();
    if (!data->mlx)
    {
        ft_printf("Failed to initialize\n");
        free_list(head);
        return(1);
    }
    data->win = mlx_new_window(data->mlx, 800, 600, "Dahani_game");
    if (!data->win)
    {
        ft_printf("Failed to create the game\n");
        free_list(head);
        return(1);
    }
    return(0);
}


int main(void)
{
    t_list *head = NULL;
    t_data *data = init_data(&head);
    int i;

    if (!data)
    {
        printf("Failed to initialize game data.\n");
        return (1);
    }
    i = initialize_miniLibx(data, head);
    if (i == 1)
        return 1;
    free_list(head);
    return (0);
}

