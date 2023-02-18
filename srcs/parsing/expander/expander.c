/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:13:17 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:22:04 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int handle_dolar_sign(char *lexem, char **pids)
{
    char    *pid;
    int     i;

    i = 0;
    pid = ft_itoa(getppid());
    (*pids) = ft_strdup("");
    while (lexem[i] == EXPAND_)
    {
        if (lexem[i] == EXPAND_ && lexem[i + 1] == EXPAND_)
        {
            (*pids) = ft_strjoin((*pids), pid);
            i += 2;
        }
        else
        {
            (*pids) = ft_strjoin((*pids), "$");
            i++;
        }
    }
    return (i);
}

void    lexem_matching(t_data *data)
{
    int     i;
    int     is_expandable;
    char    *lexem;
    char    *pids;

    pids = NULL;
    lexem = ft_strdup(data->tokens->lex);
    free(data->tokens->lex);
    data->tokens->lex = NULL;

    i = handle_dolar_sign(lexem, &pids);
    is_expandable = (i % 2);

    if (is_expandable && lexem[i])
        expandable(data, lexem, pids);

    else if (!is_expandable && lexem[i])
        unexpandable(data, lexem, pids);

    else
        non_param(data, lexem, pids);
    free (lexem);
    free(pids);
}

t_tokens    *expander (t_data *data)
{
    t_tokens    *head;

    head = data->tokens;
    while (data->tokens != NULL)
    {
        if (data->tokens->type == EXPAND_)
            lexem_matching(data);
        data->tokens = data->tokens->next;
    }
    return (head);
}