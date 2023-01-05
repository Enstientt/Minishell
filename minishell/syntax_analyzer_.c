#include"minishell.h"

void    generate_err(t_data *data, char *input, char *err)
{
    printf("Minishell: %s: %s\n", input, err);
    data->err = 1;
}

// "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error

void    abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
    char    *temp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    temp = data->token->lex;
    free(data->token->lex);
    data->token->lex = malloc(sizeof(char) * (lexem_len - n_quotes));
    while (temp[i] == data->token->type)
        i++;
    while (temp[i] != data->token->type && temp[i] != '\0')
        data->token->lex[j++] = temp[i++];
    data->token->lex[j] = '\0';
}


int check_quotes(char *lexem, int type)
{
    int i;
    int first;
    int last;
    int content;

    first = 0;
    last = 0;
    content = 0;
    while (lexem[first] == type)
        first++;
    i = first;
    while (lexem[i] != type && lexem[i] != '\0')
    {
        content++;
        i++;
    }
    while (lexem[i++] == type)
        last++;
    if (first != last && content > 1)
        return (-1);
    return (first + last);
}