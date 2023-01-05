/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes  & ESCAP
/// Option : option with single op-Character / many op-characters

#include "minishell.h"

int keyword_syntax(t_data *data);

/// input: echo \ PWD variable: $PWD /  "LOGNAME var: $LOGNAME" ; ls -l
/// Expected output: PWD variable: /Users/ahammout/Desktop/minishell / LOGNAME var: ahammout
///                                /Users/ahammout/Desktop/minishell
// int escap_syntax(t_data *data)
// {

// }


// EX = $$$$$PATH
int expand_syntax(t_data *data)
{
    int d_sign;

    d_sign = expander(data, data->token->lex);
    if (d_sign > 1)
        data->token->type = KEYWORD;
    return (0);
}
/// Escap character inside quotes: ODD number of escap char ==> ERR ; Even number of escap ==> Display half 
int quotes_syntax(t_data *data)
{
    int i;
    int n_quotes;

    i = 0;
    n_quotes = check_quotes(data->token->lex, data->token->type);
    if (n_quotes == -1)
    {
        generate_err(data, data->token->lex, "inclosed quotes");
        return (1);
    }
    /// Expand part
    while (data->token->lex[i] == data->token->type)
        i++;
    while (data->token->lex[i] != data->token->type && data->token->lex[i] != '\0')
    {
        if (data->token->lex[i] == EXPAND_)
            i += expander(data, data->token->lex + i);
        i++;
    }
    abs_syntax(data, ft_strlen(data->token->lex), n_quotes);
    return (0);
}

//// SYNTAX CHECKER : return a tokenzed linked list in seccuss;

t_tokens    *syntax_checker(t_data *data)
{
    t_tokens    *ptr;

    ptr = data->token;
    while (data->token != NULL)
    {
        if (data->token->type == SQUOTE || data->token->type == DQUOTE)
        {
            if (quotes_syntax(data))
                return (ptr);
        }
        else if (data->token->type == EXPAND_)
            expand_syntax(data);
        // else if (data->token->type == ESCAP)
        //     escap_syntax(data);
        // else if (data->token->type == REDIN || data->token->type == APPEND 
        //     || data->token->type == HEREDOC || data->token->type == SEPERATOR)
        //     operator_syntax(data);
        // else
        // {
        //     if (keyword_syntax(data))
        //         return (ptr);
        // }
        data->token  = data->token->next;
    }
    // printf("Checked by Success.\n\n");
    return (ptr);
}