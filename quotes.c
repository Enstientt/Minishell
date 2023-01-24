#include"minishell.h"

void    abs_syntax(t_data *data, int lexem_len, int n_quotes)
{
    char    *temp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    temp = ft_strdup(data->token->lex);
    free(data->token->lex);

    if (lexem_len - n_quotes == 0)
    {
        data->token->lex = NULL;
        data->token->type = EMPTY;
    }
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
        data->token->type = KEYWORD;
    }
    free (temp);
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
    int n_quotes;

    n_quotes = check_quotes(data->token->lex, data->token->type);
    if (n_quotes == -1)
    {
        printf("Minishell: %s: %s\n", data->token->lex, "Inclosed quotes");
        data->err = 1;
        return (1);
    }
    abs_syntax(data, ft_strlen(data->token->lex), n_quotes);
    return (0);
}
