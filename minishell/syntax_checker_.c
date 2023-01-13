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

void    check_keyword(t_data *data)
{
    int i;

    i = 0;
    while (data->token->lex[i])
    {
        // if (data->token->lex[i] == EXPAND_)
        //     expander(data, data->token->lex + i);
        i++;
    }
}