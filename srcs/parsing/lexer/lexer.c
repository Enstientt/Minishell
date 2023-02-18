/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:13:35 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:21:17 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int special_op(t_data *data, char *lexem, int type)
{
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] == type)
        ref.l++;
    data->tokens->lenght = ref.l;
    data->tokens->lex = malloc(sizeof(char) * ref.l + 1);
    if (!data->tokens->lex)
        exit_error(data, 1, "Minishell: Allocation failed.");
    while (lexem[ref.i] == type)
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    optype(data->tokens->lenght, type, data->tokens);
    return (ref.i);
}

int keyword(t_data *data, char *lexem)
{
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] && is_keyword(lexem[ref.l]))
        ref.l++;
    data->tokens->lenght = ref.l;
    data->tokens->lex = malloc(sizeof(char) * ref.l + 1);
    if (!data->tokens->lex)
        exit_error(data, 1, "Minishell: Allocation failed.");
    while (lexem[ref.i] && is_keyword(lexem[ref.i]))
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    data->tokens->type = KEYWORD;
    return (ref.i);
}

int expand(t_data *data, char *lexem)
{
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] == EXPAND_ || lexem[ref.l] == '@' || lexem[ref.l] == '*')
        ref.l++;
    while (ft_isalpha(lexem[ref.l]) || ft_isdigit(lexem[ref.l]) || lexem[ref.l] == '_')
        ref.l++;
    data->tokens->lex = malloc(sizeof(char) * ref.l);
    if (!data->tokens->lex)
        exit_error(data, 1, "Minishell: Allocation failed.");
    while (lexem[ref.i] == EXPAND_ || lexem[ref.i] == '@' || lexem[ref.i] == '*')
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    while (ft_isalpha(lexem[ref.i]) || ft_isdigit(lexem[ref.i]) || lexem[ref.i] == '_')
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    data->tokens->type = EXPAND_;
    return (ref.i);
}

int quotes(t_data *data, char *lexem, char type)
{
    t_reference ref;
    int         quote;

    quote = 0;
    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l])
    {
        if (lexem[ref.l] == type)
            quote++;
        ref.l++;
        if (quote == 2)
            break;
    }
    data->tokens->lex = malloc(sizeof(char) * ref.l + 1);
    if (!data->tokens->lex)
        exit_error(data, 1, "Minishell: Allocation failed.");
    quote = 0;
    while (lexem[ref.i])
    {
        if (lexem[ref.i] == type)
            quote++;
        data->tokens->lex[ref.j++] = lexem[ref.i++];
        if (quote == 2)
            break;
    }
    data->tokens->lex[ref.j] = '\0';
    data->tokens->type = type;
    return (ref.i);
}

int white_space(t_data *data, char *lexem)
{
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    while (lexem[ref.l] && is_whitespace(lexem[ref.l]))
        ref.l++;
    data->tokens->lex = malloc(sizeof(char) * ref.l + 1);
    if (!data->tokens->lex)
        exit_error(data, 1, "Minishell: Allocation failed.");
    while (lexem[ref.i] && is_whitespace(lexem[ref.i]))
        data->tokens->lex[ref.j++] = lexem[ref.i++];
    data->tokens->lex[ref.j] = '\0';
    data->tokens->type = WHITE;
    return (ref.i);
}

t_tokens *lexer(t_data *data)
{
    int         i;
    int         add_node;
    t_tokens    *head;
    
    head = NULL;
    if (white_check (data->buffer))
    {
        i = 0;
        add_node = 0;
        init_list(data);
        head = data->tokens;
        while (data->buffer[i])
        {
            create_new_node(data, &add_node);
            if (is_whitespace(data->buffer[i]))
                i += white_space(data, data->buffer + i);
            else if (is_quoted(data->buffer[i]))
                i += quotes(data, data->buffer + i, data->buffer[i]);
            else if (data->buffer[i] == EXPAND_)
                i += expand(data, data->buffer + i);
            else if (is_keyword(data->buffer[i]))
                i += keyword(data, data->buffer + i);
            else if (is_special_op(data->buffer[i]))
                i += special_op(data, data->buffer + i, data->buffer[i]);
        }
    }
    return (head);
}