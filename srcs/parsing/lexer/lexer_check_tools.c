/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:46:54 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:21:32 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int is_special_op(char c)
{
    if (c == REDIN || c == REDOUT || c == PIPE)
        return (1);
    return (0);
}

int is_whitespace(char c)
{
    if ((c == ' ' || c == '\t'))
        return (1);
    return (0);
}

int is_quoted(char c)
{
    if ((c == DQUOTE || c == SQUOTE))
        return (1);
    return (0);
}

int is_keyword(char c)
{
    if (!is_quoted(c) && !is_special_op(c) \
        && !is_whitespace(c) && c != EXPAND_ \
         &&  c != '\0')
        return (1);
    return (0);
}