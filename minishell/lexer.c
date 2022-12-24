#include"minishell.h"

    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
    // INCLUDE THE QUOTING ON THE LEX STRING.

int is_sentence(t_data *data, char *buff, t_tokens *tmp, char quote)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (quote == '\\')
    {
        while (is_escap(buff[i]))
        {
            tmp->lex[j] = buff[i];
            j++;
            i++;
        }
    }
    tmp->type = quote;
    add_new_node(data, tmp);
    tmp = tmp->next;
    return(0);
}

int lexer(t_data *data)
{
    int         i;
    t_tokens    *tmp;

    i = 0;
    data->tokens = malloc(sizeof(t_tokens));
    data->tokens->next = NULL;
    tmp = data->tokens;
    while (data->buffer[i])
    {
        // / SENTENCE / COMMAND CASES : SINGLE / DOUBLE QUOTES & ESCAPE
        printf("index_1: %d\n", i);
        if (data->buffer[i] == SQUOTE)
            i += is_sentence(data, data->buffer + i, tmp, SQUOTE);
        else if (data->buffer[i] == DQUOTE)
            i += is_sentence(data, data->buffer + i, tmp, DQUOTE);
        else if (data->buffer[i] == ESCAP)
            i += is_sentence(data, data->buffer + i, tmp, ESCAP);
        printf("index_2: %d\n", i);
    }
    //     // File comes after those : REDIRECTION / APPEND OUTPUT
    //     else if (data->buffer[i] == REDOUT && data->buffer[i + 1] == REDOUT)
    //     {

    //     }
    //     else if (data->buffer[i] == REDOUT)
    //     {

    //     }

    //     // REDIRECTION / APPEND INPUT
    //     else if (data->buffer[i] == REDIN  && data->buffer[i + 1] == REDIN)
    //     {

    //     }
    //     else if (data->buffer[i] == REDIN)
    //     {

    //     }
    
    //     /// operational operators
    //     else if (data->buffer[i] == SEPERATOR)
    //     {
    //         // Sep case

    //     }
    //     else if (data->buffer[i] == PIPE)
    //     {
    //         // Pipe case

    //     }
    //     else if (data->buffer[i] == DOLARS)
    //     {
    //         // variable case

    //     }
    //     else
    //         is_keyword(data, tmp, &i);
    //     printf("%c\n", data->buffer[i]);
    //     i++;
    // }

    // DISPLAY THE LIST 
    while (data->tokens != NULL)
    {
        printf("%s\n", data->tokens->lex);
        data->tokens = data->tokens->next;
    }
    free(data->buffer);
    data->buffer = NULL;
    return (0);
}

/// Freeing the buffer when finish using it / affecting it by NULL.