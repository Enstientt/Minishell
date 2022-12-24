#include"minishell.h"

    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
    // INCLUDE THE QUOTING ON THE LEX STRING.

int keyword(t_data *data, char *buff, t_tokens **tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
        (*tmp)->lex[j++] = buff[i++];
    (*tmp)->type = KEYWORD;
    add_new_node(data, (*tmp));
    (*tmp) = (*tmp)->next;
    return (i);
}


int sentence(t_data *data, char *buff, t_tokens **tmp, char quote)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (quote == ESCAP)
    {
        while (is_quoted(buff[i]))
            (*tmp)->lex[j++] = buff[i++];
    }
    else if (quote == SQUOTE || quote == DQUOTE)
    {
        while (buff[i] == quote)
            (*tmp)->lex[j++] = buff[i++];
        while (buff[i] != quote && buff[i] != '\0')
            (*tmp)->lex[j++] = buff[i++];
        while (buff[i] == quote)
            (*tmp)->lex[j++] = buff[i++];
    }
    (*tmp)->type = quote;
    add_new_node(data, (*tmp));
    (*tmp) = (*tmp)->next;
    return(i);
}

int lexer(t_data *data)
{
    int         i;
    t_tokens    *tmp;

    i = 0;
    data->tokens = malloc(sizeof(t_tokens));
    data->tokens->lex = ft_strdup("");
    data->tokens->next = NULL;
    tmp = data->tokens;
    while (data->buffer[i])
    {
        while(data->buffer[i] == ' ' || data->buffer[i] == '\t')
            i++;
        if (data->buffer[i] == SQUOTE)
            i += sentence (data, data->buffer + i, &tmp, SQUOTE);
        else if (data->buffer[i] == DQUOTE)
            i += sentence (data, data->buffer + i, &tmp, DQUOTE);
        else if (data->buffer[i] == ESCAP)
            i += sentence (data, data->buffer + i, &tmp, ESCAP);
        else if (data->buffer[i] == PIPE)
        {
            
        }
        else
            i += keyword(data, data->buffer + i, &tmp);
    }
    display_list(data);
    free(data->buffer);
    data->buffer = NULL;
    return (0);
}

/// Freeing the buffer when finish using it / affecting it by NULL.