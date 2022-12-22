#include"minishell.h"

int sentence(t_data *data, int *index, char quote)
{
    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
    // INCLUDE THE QUOTING ON THE LEX STRING.

    if (data->buffer[*index] == '\'')
    {
        while (data->buffer[*index] != quote)
        {
            
            *index++;
        }
    }
    else if (data->buffer[*index] == '\"')
    {

    }
    else if (data->buffer[*index] == '\\')
    {

    }
}

int lexer(t_data *data)
{
    int     i;

    i = 0;
    data->token = malloc(sizeof(t_tokens));
    while (data->buffer[i])
    {
        /// SENTENCE / COMMAND CASES : SINGLE / DOUBLE QUOTES & ESCAPE
        if (data->buffer[i] == SQUOTE)
            sentence(data, &i, SQUOTE);
        else if (data->buffer[i] == DQUOTE)
            sentence(data, &i, DQUOTE);
        else if (data->buffer[i] == ESCAP)
            sentence(data, &i, ESCAP);

        else if (data->buffer[i] == OPTION)
        {

        }
        
        // File comes after those : REDIRECTION / APPEND OUTPUT
        else if (data->buffer[i] == REDOUT && data->buffer[i + 1] == REDOUT)
        {

        }
        else if (data->buffer[i] == REDOUT)
        {

        }

        // REDIRECTION / APPEND INPUT
        else if (data->buffer[i] == REDIN  && data->buffer[i + 1] == REDIN)
        {

        }
        else if (data->buffer[i] == REDIN)
        {

        }
    
        /// operational operators
        else if (data->buffer[i] == SEPERATOR)
        {
            // Sep case

        }
        else if (data->buffer[i] == PIPE)
        {
            // Pipe case

        }
        else if (data->buffer[i] == DOLARS)
        {
            // variable case

        }
        i++;
    }
    return (0);
}