/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 13:06:50 by ahammout         ###   ########.fr       */
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
        exit(EXIT_FAILURE);
    }
    return (0);
    
}
