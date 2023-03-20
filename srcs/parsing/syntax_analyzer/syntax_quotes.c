/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:23:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/10 19:44:13 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
    char        *lexem;
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    lexem = ft_strdup(data->tokens->lex);
    free(data->tokens->lex);
    if ((lexem_len - n_quotes) == 0)
    {
        data->tokens->lex = NULL;
        data->tokens->type = EMPTY;
    }
    else
    {
        data->tokens->lex = malloc(sizeof(char) * (lexem_len - n_quotes));
        if (!data->tokens->lex)
            exit_error(data, "Minishell: Allocation failed.");
        while (lexem[ref.i] == data->tokens->type)
            ref.i++;
        while (lexem[ref.i] && lexem[ref.i] != data->tokens->type)
            data->tokens->lex[ref.j++] = lexem[ref.i++];
        data->tokens->lex[ref.j] = '\0';
    }
    free (lexem);
}

int quotes_syntax(char *lexem, int type)
{
    int i;
    int n_q;

    i = 0;
    n_q = 0;
    while (lexem[i])
    {
        if (lexem[i] == type)
            n_q++;
        i++;
    }
    if (n_q == 2)
        return (n_q);
    return (-1);
}

int analyze_quotes (t_data *data)
{
    int n_quotes;

    if (data->tokens->type == DQUOTE || data->tokens->type == SQUOTE)
    {
        n_quotes = quotes_syntax (data->tokens->lex, data->tokens->type);
        if (n_quotes == -1)
        {
            printf("Minishell: %s: %s\n", data->tokens->lex, "Inclosed quotes");
            data->err = 1;
            return (0);
        }
        abs_syntax(data, ft_strlen(data->tokens->lex), n_quotes);
        if (!data->tokens->lex || ft_strchr(data->tokens->lex, DQUOTE)
            || data->tokens->type == SQUOTE || data->tokens->prev->type == HEREDOC)
        {
            data->tokens->type = KEYWORD;   
            return (1);
        }
        data->tokens->type = KEYWORD;
        if (ft_strchr(data->tokens->lex, EXPAND_))
            split_token(data);
    }
    return (1);
}
