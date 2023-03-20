/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:45:24 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/21 00:57:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int q_keyword(t_data *data, char *lexem)
{
    t_reference ref;

    ref.i = 0;
    ref.l = 0;
    ref.j = 0;
    while (lexem[ref.l] && lexem[ref.l] != EXPAND_)
        ref.l++;
    data->tokens->lex = malloc(sizeof(char) * ref.i);
    if (!data->tokens->lex)
        exit_error(data, "Minishell: Allocation failed.");
    while (lexem[ref.i] && lexem[ref.i] != EXPAND_)
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    data->tokens->type = KEYWORD;
    return (ref.i);
}

void split_token(t_data *data)
{
    int     i;
    int     add_node;
    char     *lexem;
    t_tokens *head;
    t_tokens *next;

    head = data->tokens;
    next = data->tokens->next;
    lexem = ft_strdup(data->tokens->lex);
    free(data->tokens->lex);
    add_node = 0;
    i = 0;
    while (lexem[i])
    {
        create_new_node(data, &add_node);
        if (lexem[i] == EXPAND_)
            i += expand(data, lexem + i);
        else if (lexem[i] && lexem[i] != EXPAND_)
            i += q_keyword(data, lexem + i);
        data->tokens->next = next;
    }
    data->tokens = head;
    free(lexem);
}