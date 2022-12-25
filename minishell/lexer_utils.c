/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:51 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 13:07:01 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// FUNCTION USED FOR LEXER PART.
// FREE THE TOKENS LIST  && THE INPUT BUFFER
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

int is_escap(char c)
{
    if (c != '>' && c != '<' && c != '|' 
        && c != ';' && c != '\0' && c != '\'' 
        && c != '\"')
        return (1);
    return (0); 
}

int add_new_node(t_data *data, t_tokens *tmp)
{
    t_tokens    *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_error(data, 1, "Malloc: allocation failed.");
    node->next = NULL;
    tmp->next = node;
    return (0);
}

void    display_list(t_data *data)
{
    int n;

    n = 0;
    // DISPLAY THE LIST 
    while (data->tokens != NULL)
    {
        printf("---- Node %d ----\nLexeme: %s\nType: %d\n\n", n, data->tokens->lex, data->tokens->type);
        n++;
        data->tokens = data->tokens->next;
    }
}
