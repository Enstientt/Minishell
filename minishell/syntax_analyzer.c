/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes
/// Option : option with single op-Character / many op-characters

#include "minishell.h"

// Valid syntax = echo "Hello, World" > file 
// Valid syntax = echo ""
// LAST TOKEN INVALID CASES: &&, ||, |, ;, >>, >, ~
int analyze_redin_append(t_data *data)
{
    t_tokens    *tmp;

    tmp = data->token;
    printf("size of append: %d\n", data->token->lenght);
    if (data->token->type == REDOUT)
    {
        tmp = tmp->next;
        if (tmp->type == PIPE || tmp->type == SEMICOLONE 
            || tmp->type == AND || tmp->type == TILD 
            || tmp->type == ASTERISK)
        {
            generate_err(data, data->token->le)
        }
    }
    exit(0);
}
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
        printf("Minishell: %s: %s\n", data->token->lex, "Inclosed quotes");
        data->err = 1;
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
/// Check For the first node; if it is an operator : generate error.
t_tokens    *syntax_checker(t_data *data)
{
    t_tokens    *ptr;

    ptr = data->token;
    /// ANALYZE THE FIRST/LAST TOKENS : the first node deosn't need to be an operator;
    // analyze_first_end(data);
    while (data->token != NULL)
    {
        if (data->token->type == SQUOTE || data->token->type == DQUOTE)
        {
            if (quotes_syntax(data))
                return (ptr);
        }
        else if (data->token->type == EXPAND_)
            expand_syntax(data);
        else if (data->token->type == REDOUT || data->token->type == APPEND)
        {
            printf("Entered Here\n");
            if (analyze_redin_append(data))
                return (ptr);
        }
        data->token  = data->token->next;
    }
    // printf("Checked by Success.\n\n");
    return (ptr);
}