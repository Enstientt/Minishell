/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:51 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/13 11:13:57 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void optype(int size, int type, t_tokens *token)
{
    if (size == 1 && type == REDOUT)
        token->type = REDOUT;
    else if (size > 1 && type == REDOUT)
        token->type = APPEND;
    else if (size == 1 && type == REDIN)
        token->type = REDIN;
    else if (size > 1 && type == REDIN)
        token->type = HEREDOC;
    else if (type == PIPE)
        token->type = PIPE;
}

int is_space_or_tab(char *buffer)
{
    int i;

    i = 0;
    while(buffer[i] == ' ' || buffer[i] == '\t')
        i++;
    return (i);
}

int is_escap(char c)
{
    if (c != '>' && c != '<' && c != '|' 
        && c != ';' && c != '\0' && c != '\'' 
        && c != '\"')
        return (1);
    return (0); 
}

void    add_new_node(t_data *data)
{
    t_tokens    *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_error(data, 1, "Malloc: allocation failed.");
    node->next = NULL;
    data->token->next = node;
}

void    init_list(t_data *data)
{
    data->token = malloc(sizeof(t_tokens));
    if (!data->token)
        exit_error(data, 1, "Minishell: Allocation failed.");
    data->token->next = NULL;
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
