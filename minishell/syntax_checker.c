/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes  & ESCAP
/// Option : option with single op-Character / many op-characters

#include "minishell.h"


void    error_generator(t_data *data, char *input, char *err)
{
    printf("Minishell: %s: %s", input, err);
    free(data->buffer);
    while (data->tokens != NULL)
    {
        free(data->tokens->lex);
        free(data->tokens);
        data->tokens = data->tokens->next;
    }
    exit(EXIT_FAILURE);
}

// "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
void    expand_check_quotes(t_data *data, t_tokens *tmp, t_tokens *to_free)
{
    int i;
    int first;
    int last;

    first = 0;
    last = 0;
    while (tmp->lex[i])
    {
        while (tmp->lex[i++] == tmp->type)
            first++;
        while (tmp->lex[i] != tmp->type)
        {
            if (tmp->lex[i] == EXPAND_)
                expand(data, tmp);
            i++;
        }
        while (tmp->lex[i] == tmp->type)
            last++;
        if (first != last)
        {
            free_tmp(to_free);
            error_generator(data, tmp->lex, "inclosed quotes");
        }
    }
}


int syntax_checker (t_data *data)
{
    t_tokens    *tmp;
    t_tokens    *to_free;

    tmp = data->tokens;
    to_free = tmp;
    while (tmp != NULL)
    {
        if (tmp->type == SQUOTE || tmp->type == DQUOTE)
            expand_check_quotes(data, tmp);
        else if (tmp->type == ESCAP)
            expand_check_escap(data, tmp);
        else if (tmp->type == REDIN || tmp->type == APPEND || tmp->type == HEREDOC || tmp->type == SEPERATOR)
            operator_check(data, tmp, to_free);
        tmp  = tmp->next;
    }
    return (0);
}