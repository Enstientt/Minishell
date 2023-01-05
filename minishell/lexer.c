/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/05 12:01:17 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

                // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
                // INCLUDE THE QUOTING ON THE LEX STRING.



#include"minishell.h"

// Buff = "$$$$PATH"

int expand (t_data *data, char *buff)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    data->token->lex = malloc (sizeof(char) * len);
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
    {
        data->token->lex[i] = buff[i];
        i++;
    }
    data->token->lex[i] = '\0';
    data->token->type = EXPAND_;
    return (i);
}

t_tokens *lexer(t_data *data)
{
    int         i;
    int         add_node;
    t_tokens    *ptr;
    
    ptr = NULL;
    if (non_white(data->buffer))
    {
        i = 0;
        add_node = 0;
        data->token = malloc(sizeof(t_tokens));
        if (!data->token)
            exit_error(data, 1, "Minishell: Allocation failed.");
        data->token->next = NULL;
        ptr = data->token;
        while (data->buffer[i])
        {
            if (data->buffer[i] == ' ' || data->buffer[i] == '\t')
                while(data->buffer[i] == ' ' || data->buffer[i] == '\t')
                    i++;
            else if (data->buffer[i] != ' ' && data->buffer[i] != '\t' && data->buffer != '\0')
            {
                if (data->buffer[i] == SQUOTE)
                {
                    if (add_node)
                    {
                        add_new_node (data);
                        data->token = data->token->next;
                    }
                    i += quotes (data, data->buffer + i, SQUOTE);
                    add_node = 1;
                }
                else if (data->buffer[i] == DQUOTE)
                {
                    if (add_node)
                    {
                        add_new_node (data);
                        data->token = data->token->next;
                    }
                    i += quotes (data, data->buffer + i, DQUOTE);
                    add_node = 1;
                }
                else if (data->buffer[i] == ESCAP)
                {
                    if (add_node)
                    {
                        add_new_node (data);
                        data->token = data->token->next;
                    }
                    i += escap (data, data->buffer + i);
                    add_node = 1;
                }
                else if (data->buffer[i] == REDOUT)
                {
                    if (add_node)
                    {
                        add_new_node (data);
                        data->token = data->token->next;
                    }
                    i += operator(data, data->buffer + i, REDOUT);
                    add_node = 1;
                }
                else if (data->buffer[i] == REDIN)
                {
                    if (add_node)
                    {
                        add_new_node(data);
                        data->token = data->token->next;
                    }
                    i += operator(data, data->buffer + i, REDIN);
                    add_node = 1;
                }
                else if (data->buffer[i] == SEPERATOR)
                {
                    if (add_node)
                    {
                        add_new_node(data);
                        data->token = data->token->next;
                    }
                    i += operator(data, data->buffer + i, SEPERATOR);
                    add_node = 1;

                }
                else if (data->buffer[i] == PIPE)
                {
                    if (add_node)
                    {
                        add_new_node(data);
                        data->token = data->token->next;
                    }
                    i += operator(data, data->buffer + i, PIPE);
                    add_node = 1;
                }
                else if (data->buffer[i] == EXPAND_)
                {
                    if (add_node)
                    {
                        add_new_node(data);
                        data->token = data->token->next;
                    }
                    i += expand (data, data->buffer + i);
                    add_node = 1;
                }
                else
                {
                    if (add_node)
                    {
                        add_new_node(data);
                        data->token = data->token->next;
                    }
                    i += keyword(data, data->buffer + i);
                    add_node = 1;
                }
            }
        }
    }
    return (ptr);
}

/// Freeing the buffer when finish using it / affecting it by NULL.