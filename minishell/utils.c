/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 14:51:00 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int exit_error(t_data *data, int option, char *err)
{
    /// FREE JUST THE BUFFER && DISPLAY ERROR
    if (option == 1)
    {
        free(data->buffer);
        printf("%s\n", err);
    }
    else if (option == 2)
    {
        free(data->buffer);
        while (data->tokens != NULL)
        {
            free(data->buffer);
            data->tokens = data->tokens->next;
        }
    }
    exit(EXIT_FAILURE);
    return (0);
}
