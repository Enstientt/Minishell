#include"minishell.h"
// "union quoted "union quoted "Union Quoted "Union quoted""""    [v]
//  echo "hello, World "Here is again "Expand this $PWD UNION  """""   [v]

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
/// Calucatate the number of quotes: if (n_q % 2 = 0) then get abs_syntax

int check_quotes(char *lexem, int type)
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
    if (n_q % 2 == 0)
        return (n_q);
    return (-1);
}

//  echo "" | ls -l | touch file | echo "This on The file" > file 
// echo "Put this on the file  "Expand PWD ==> $PWD""
int quotes_syntax(t_data *data)
{
    int i;
    int n_quotes;

    i = 0;
    n_quotes = check_quotes(data->token->lex, data->token->type);
    if (n_quotes == -1)
    {
        printf("Minishell: %s: %s\n", data->token->lex, "Inclosed quotes");
        data->err = 1;
        return (1);
    }
    /// Expand part
    while (data->token->lex[i])
    {
        if (data->token->lex[i] == EXPAND_)
            i += expander(data, data->token->lex + i);
        i++;
    }
    // abs_syntax(data, ft_strlen(data->token->lex), n_quotes);
    return (0);
}
