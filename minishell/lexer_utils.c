/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:51 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/02 15:44:30 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_escap(char c)
{
    if (c != '>' && c != '<' && c != '|' 
        && c != ';' && c != '\0' && c != '\'' 
        && c != '\"')
        return (1);
    return (0); 
}

int     add_new_node(t_data *data)
{
    t_tokens    *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_error(data, 1, "Malloc: allocation failed.");
    node->next = NULL;
    data->token->next = node;
    return (0);
}

void    display_list(t_tokens *token)
{
    int n;
    t_tokens *tmp;

    n = 0;
    tmp = token;
    while (tmp != NULL)
    {
        printf("---- Node %d ----\nLexeme: %s\nType: %d\n\n", n, tmp->lex, tmp->type);
        n++;
        tmp = tmp->next;
    }
}
