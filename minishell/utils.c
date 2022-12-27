/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/27 19:15:21 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/// FUNCTION USED TO FREE THE DATA. ///
/*
    PART - 1: FREE TOKENS LIST  && INPUT BUFFER
*/
void    free_data(t_data *data)
{
    free(data->buffer);
    data->buffer = NULL;
    while (data->tokens != NULL)
    {
        free(data->tokens->lex);
        free(data->tokens);
        data->tokens = data->tokens->next;
    }
}

void exit_error(t_data *data, int option, char *err)
{
    /// FREE JUST THE BUFFER && DISPLAY ERROR.
    if (option == 1)
    {
        free(data->buffer);
        printf("%s\n", err);
    }
    /// THIS IS FOR LEXER PART.
    else if (option == 2)
    {
        free(data->buffer);
        while (data->tokens != NULL)
        {
            free(data->tokens->lex);
            free(data->tokens);
            data->tokens = data->tokens->next;
        }
    }
    exit(EXIT_FAILURE);
}
