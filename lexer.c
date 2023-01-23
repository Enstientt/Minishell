/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/16 19:26:29 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

                // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
                // INCLUDE THE QUOTING ON THE LEX STRING.



#include"minishell.h"

// Buff = "$$$$PATH"

int non_operator(char c)
{
    if (c != SQUOTE && c != DQUOTE && c != REDIN && c != REDOUT && c != PIPE)
        return (1);
    return (0);
}

int is_expand(t_data *data, char *buffer, int *add_node)
{
    int i;

    i = 0;
    if (buffer[i] == EXPAND_)
    {
        if (*add_node)
        {
            add_new_node(data);
            data->token = data->token->next;
        }
        i += expand(data, buffer + i);
        *add_node = 1;
    }
    return (i);
}

int is_keyword(t_data *data, char *buffer, int *add_node)
{
    int i;

    i = 0;
    if (non_operator(buffer[i]) && buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\t')
    {
        if (*add_node)
        {
            add_new_node (data);
            data->token = data->token->next;
        }
        i += keyword(data, buffer + i);
        *add_node = 1;
    }
    return (i);
}

int is_pipe (t_data *data, char *buffer, int *add_node)
{
    int i;

    i = 0;
    if (buffer[i] == PIPE)
    {
        if (*add_node)
        {
            add_new_node(data);
            data->token = data->token->next;
        }
        i += operator (data, buffer + i, buffer[i]);
        *add_node = 1;
    }
    return (i);
}
int is_redirection (t_data *data, char *buffer, int *add_node)
{
    int i;
    
    i = 0;
    if (buffer[i] == REDOUT || buffer[i] == REDIN)
    {
        if (*add_node)
        {
            add_new_node (data);
            data->token = data->token->next;
        }
        i += operator (data, buffer + i, buffer[i]);
        *add_node = 1;
    }
    return (i);
}

int is_quoted(t_data *data, char *buffer, int *add_node)
{
    int i;

    i = 0;
    if (buffer[i] == SQUOTE || buffer[i] == DQUOTE)
    {
        if (*add_node)
        {
            add_new_node (data);
            data->token = data->token->next;
        }
        i += quotes (data, buffer + i, buffer[i]);
        *add_node = 1;
    }
    return (i);
}

t_tokens *lexer(t_data *data)
{
    int         i;
    int         add_node;
    t_tokens    *ptr;
    
    ptr = NULL;
    if (non_white (data->buffer))
    {
        i = 0;
        add_node = 0;
        init_list(data);
        ptr = data->token;
        while (data->buffer[i])
        {
            if (data->buffer[i] == ' ' || data->buffer[i] == '\t')
                i += is_space_or_tab (data->buffer + i);
            else if (data->buffer[i] != ' ' && data->buffer[i] != '\t' && data->buffer[i] != '\0')
            {
                i += is_quoted (data, data->buffer + i, &add_node);
                i += is_redirection (data, data->buffer + i, &add_node);
                i += is_pipe (data, data->buffer + i, &add_node);
                i += is_expand (data, data->buffer + i, &add_node);
                i += is_keyword (data, data->buffer + i, &add_node);
            }
        }
    }
    return (ptr);
}