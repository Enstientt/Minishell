#include"minishell.h"
// "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error

/// CMD INVALID BEGIN : & , ; , | , ||

int invalid_begin(t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE) 
        || (token->lex[0] == AND && token->lex[1] == AND))
    {
        printf("Minishell: syntax error near unexpected token `%c%c'\n", token->lex[0], token->lex[1]);
        return (1);
    }
    else if (token->lex[0] == AND || token->lex[0] == SEMICOLONE
        || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `%c'\n", token->lex[0]);
        return (1);
    }
    return (0);
}

/// CMD INVALID END : & , ; , > , >> , < , << , | , || , && , ( , )
/// specifieng error: bash-3.2$ echo "fdsvsv" > >
//                    bash: syntax error near unexpected token `>'

int invalid_file(t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE)
        || (token->lex[0] == AND && token->lex[1] == AND)
        || (token->lex[0] == REDIN && token->lex[1] == REDIN)
        || (token->lex[0] == REDOUT && token->lex[1] == REDOUT))
    {
        printf("Minishell: syntax error near unexpected token `%c%c'\n", token->lex[0], token->lex[1]);
        return (1);
    }
    else if (token->lex[0] == REDIN || token->lex[0] == REDOUT 
            || token->lex[0] == AND || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `%c'\n", token->lex[0]);
        return (1);
    }
    return (0);
}

int invalid_end(t_tokens *token)
{
    if ((token->lex[0] == PIPE && token->lex[1] == PIPE)
        || (token->lex[0] == AND && token->lex[1] == AND)
        || (token->lex[0] == REDIN && token->lex[1] == REDIN)
        || (token->lex[0] == REDOUT && token->lex[1] == REDOUT))
    {
        printf("Minishell: syntax error near unexpected token `newline'\n");
        return (1);
    }
    else if (token->lex[0] == REDIN || token->lex[0] == REDOUT 
            || token->lex[0] == AND || token->lex[0] == PIPE)
    {
        printf("Minishell: syntax error near unexpected token `newline'\n");
        return (1);
    }
    return (0);
}

void    abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
    char    *temp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    temp = data->token->lex;
    free(data->token->lex);
    if (lexem_len - n_quotes == 0)
        data->token->lex = NULL;
    else
    {
        data->token->lex = malloc(sizeof(char) * (lexem_len - n_quotes));
        if (!data->token->lex)
            exit_error(data, 2, "Minishell: Allocation failed.");
        while (temp[i] == data->token->type)
            i++;
        while (temp[i] != data->token->type && temp[i] != '\0')
            data->token->lex[j++] = temp[i++];
        data->token->lex[j] = '\0';
    }
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

int expand_var(t_data *data)
{
    int d_sign;

    d_sign = expander(data, data->token->lex);
    if (d_sign > 1)
        data->token->type = KEYWORD;
    return (0);
}