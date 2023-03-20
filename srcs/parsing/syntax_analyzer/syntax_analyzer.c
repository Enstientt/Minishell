/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:12:24 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/16 22:36:45 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
/////////// ANALYZE FUNCTIONS : Returns 1 if success OR 0 if failure ////////////////

int analyze_redirections (t_data *data)
{
    t_tokens    *token;

    if (data->tokens->type == REDOUT || data->tokens->type == APPEND \
        || data->tokens->type == REDIN || data->tokens->type == HEREDOC)
    {
        token = data->tokens;
        if (token->lenght > 2)
        {
            printf("Minishell: syntax error near unexpected token `>>'\n");
            data->err = 1;
        }
        token = token->next;
        if (!token)
        {
            printf("Minishell: syntax error near unexpected token `newline'\n");
            data->err = 1;
            return (0);
        }
        else if (!analyze_file (token))
        {
            data->err = 1;
            return (0);
        }
    }
    return (1);
}

int analyze_pipe(t_data *data)
{
    if (data->tokens->type == PIPE)
    {
        if (data->tokens->lenght > 1 || data->tokens->next == NULL)
        {
            printf("Minishell: syntax error near unexpected token `%c'\n", \
                data->tokens->lex[0]);
            data->err = 1;
            return (0);
        }
    }
    return (1);
}

int analyze_begin_end (t_data *data)
{
    t_tokens    *token;

    token = data->tokens;
    if (!analyze_begin(token))
    {
        data->err = 1;
        return (0);
    }
    if (token->next)
    {
        while (token->next && !is_metecharacter(token->type))
            token = token->next;
        if (token->next == NULL)
        {
            if (!analyze_end(token))
            {
                data->err = 1;
                return (0);
            }
        }
    }
    return (1);
}

t_tokens    *syntax_analyzer (t_data *data)
{
    t_tokens    *head;

    head = data->tokens;

    if (!analyze_begin_end(data))
        return (head);
    while (data->tokens != NULL)
    {
        if (!analyze_quotes(data))
            return (head);
        if (!analyze_pipe(data))
            return (head);
        if (!analyze_redirections(data))
            return (head);
        data->tokens  = data->tokens->next;
    }
    return (head);
}