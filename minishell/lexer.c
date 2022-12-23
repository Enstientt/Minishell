#include"minishell.h"

void sentence(t_data *data, t_tokens *tmp, int *index, char quote)
{
    // PUTING WHAT BETWEEN QUOTES OR ESCAP ON LEX STRING.
    // "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
    // INCLUDE THE QUOTING ON THE LEX STRING.
    int i;
    int j;

    i = 0;
    j = *index;
    while (data->buffer[j - 1] != quote)
    {
        tmp->lex[i] = data->buffer[j];
        j++;
    }
    *index = j;
    tmp->type = quote;
    add_new_node(data, tmp);
    tmp = tmp->next;
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
        /// SENTENCE / COMMAND CASES : SINGLE / DOUBLE QUOTES & ESCAPE
        // if (data->buffer[i] == SQUOTE)
        //     sentence(data, tmp, &i, SQUOTE);
        // else if (data->buffer[i] == DQUOTE)
        //     sentence(data, tmp, &i, DQUOTE);
        // else if (data->buffer[i] == ESCAP)
        //     sentence(data, tmp, &i, ESCAP);
        printf("%c\n", data->buffer[i]);
        i++;
    }
    data->tokens = tmp;
    return (0);
}