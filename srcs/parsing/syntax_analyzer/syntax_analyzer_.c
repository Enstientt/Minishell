/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:21:53 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int analyze_begin(t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE) 
        || (token->lex[0] == AND && token->lex[1] == AND))
    {
        printf("Minishell: syntax error near unexpected token `%c%c'\n", \
            token->lex[0], token->lex[1]);
        return (0);
    }
    else if (token->lex[0] == AND || token->lex[0] == SEMICOLONE
        || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `%c'\n", \
            token->lex[0]);
        return (0);
    }
    return (1);
}

int analyze_end(t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE) \
        || (token->lex[0] == AND && token->lex[1] == AND) \
        || (token->lex[0] == REDIN && token->lex[1] == REDIN) \
        || (token->lex[0] == REDOUT && token->lex[1] == REDOUT))
    {
        printf("Minishell: syntax error near unexpected token `newline'\n");
        return (0);
    }
    else if (token->lex[0] == REDIN || token->lex[0] == REDOUT \
        || token->lex[0] == AND || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `newline'\n");
        return (0);
    }
    return (1);
}

int analyze_file (t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE)
        || (token->lex[0] == AND && token->lex[1] == AND)
        || (token->lex[0] == REDIN && token->lex[1] == REDIN)
        || (token->lex[0] == REDOUT && token->lex[1] == REDOUT))
    {
        printf("Minishell: syntax error near unexpected token `%c%c'\n", \
            token->lex[0], token->lex[1]);
        return (0);
    }
    else if (token->lex[0] == REDIN || token->lex[0] == REDOUT 
            || token->lex[0] == AND || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `%c'\n", \
            token->lex[0]);
        return (0);
    }
    return (1);
}

int is_metecharacter(int type)
{
    if (type == REDIN || type == REDOUT || type == APPEND \
        || type == HEREDOC || type == PIPE)
        return (1);
    return (0);
}