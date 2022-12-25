/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 15:07:00 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
    // INCLUDE THE QUOTING ON THE LEX STRING.

int keyword(t_data *data, char *buff, t_tokens *tmp)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    printf("This is the buffer from keyword: %s\n", buff);
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = KEYWORD;
    return (i);
}

int escap(t_data *data, char *buff, t_tokens *tmp)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (is_escap(buff[len]))
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (is_escap(buff[i]))
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = ESCAP;
    return (i);
}

int quotes(t_data *data, char *buff, t_tokens *tmp, char quote)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;

    // COUNTING THE SIZE FOR ALLOCATION DY
    while (buff[len] == quote)
        len++;
    while (buff[len] != quote && buff[len] != '\0')
        len++;
    while (buff[len] == quote)
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (buff[i] == quote)
        tmp->lex[j++] = buff[i++];
    while (buff[i] != quote && buff[i] != '\0')
        tmp->lex[j++] = buff[i++];
    while (buff[i] == quote)
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = quote;
    return(i);
}

int lexer(t_data *data)
{
    int         i;
    int         add_node;
    t_tokens    *tmp;

    i = 0;
    add_node = 0;
    data->tokens = malloc(sizeof(t_tokens));
    data->tokens->next = NULL;
    tmp = data->tokens;
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
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += quotes (data, data->buffer + i, tmp, SQUOTE);
                add_node = 1;
            }
            else if (data->buffer[i] == DQUOTE)
            {
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += quotes (data, data->buffer + i, tmp, DQUOTE);
                add_node = 1;
            }
            else if (data->buffer[i] == ESCAP)
            {
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += escap (data, data->buffer + i, tmp);
                add_node = 1;
            }
            // File comes after those : REDIRECTION / APPEND OUTPUT
            else if (data->buffer[i] == REDOUT && data->buffer[i + 1] == REDOUT)
            {
                
            }
            else if (data->buffer[i] == REDOUT)
            {

            }

            // REDIRECTION / APPEND INPUT
            else if (data->buffer[i] == REDIN  && data->buffer[i + 1] == REDIN)
            {

            }
            else if (data->buffer[i] == REDIN)
            {

            }
        
            /// operational operators
            else if (data->buffer[i] == SEPERATOR)
            {
                // Sep case

            }
            else if (data->buffer[i] == PIPE)
            {
                // Pipe case

            }
            else if (data->buffer[i] == DOLARS)
            {
                // variable case

            }
            else
            {
                if (add_node)
                {
                    add_new_node(data, tmp);
                    tmp = tmp->next;
                }
                i += keyword(data, data->buffer + i, tmp);
                add_node = 1;
            }
        }
    }
    display_list(data);
    free(tmp);
    return (0);
}

/// Freeing the buffer when finish using it / affecting it by NULL.
