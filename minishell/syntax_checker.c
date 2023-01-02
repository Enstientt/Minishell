/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes  & ESCAP
/// Option : option with single op-Character / many op-characters

#include "minishell.h"


void    generate_err(t_data *data, char *input, char *err)
{
    printf("Minishell: %s: %s\n", input, err);
    data->err = 1;
}

// "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
        /* 
            +++++ get the absolute syntax of what between quotes; ++++++
            Arguments : data ==> struct of data,  tmp ==> the token with type |Quote|,  size of Lexeme.
        */
        //abs_syntax(data, tmp, ft_strlen(tmp->lex));

int syntax_quotes(t_data *data)
{
    int i;
    int first;
    int last;

    i = 0;
    first = 0;
    last = 0;
    while (data->token->lex[i] == data->token->type)
    {
        i++;
        first++;
    }
    while (data->token->lex[i] != data->token->type)
    {
        if (data->token->lex[i] == EXPAND_)
        {
            printf("EXPAND that variable!\n");
            i += expander(data, data->token->lex + i);
        }
        i++;
    }
    while (data->token->lex[i++] == data->token->type)
        last++;
    if (first != last)
    {
        generate_err(data, data->token->lex, "inclosed quotes");
        return (1);
    }
    return (0);
}

//// SYNTAX CHECKER : return a tokenzed linked list in seccuss;

t_tokens    *syntax_checker (t_data *data)
{
    t_tokens    *ptr;

    ptr = data->token;
    while (data->token != NULL)
    {
        if (data->token->type == SQUOTE || data->token->type == DQUOTE)
            if (syntax_quotes(data))
                return (ptr);
        // else if (data->token->type == ESCAP)
        //     syntax_quotes(data);
        // else if (data->token->type == REDIN || data->token->type == APPEND 
        //     || data->token->type == HEREDOC || data->token->type == SEPERATOR)
        //     operator_syntax(data);
        data->token  = data->token->next;
    }
    printf("Checked by Success.\n\n");
    return (ptr);
}