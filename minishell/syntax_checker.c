/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes
/// Option : option with single op-Character / many op-characters

#include "minishell.h"

/// REDOUT : INVALID FILE FORMAT ==> INVALID FILES NAME : && , || , 

// int check_pipe (t_data *data)
// {

// }

/// >

int is_metecharacter(int type)
{
    if (type == REDIN || type == REDOUT
        || type == APPEND || type == HEREDOC
        || type == PIPE)
        return (1);
    return (0);
}
int check_rederections (t_data *data)
{
    t_tokens    *token;

    token = data->token;
    /// Check The file Name : a non valid fie whose begin with a metacharacter
    if (token->lenght > 2)
        data->err = 1;
    token = token->next;
    if (invalid_end(token))
    {
        data->err = 1;
        return (1);
    }
    return (0);
}

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

int check_first_end(t_data *data)
{
    t_tokens    *token;

    token = data->token;
    if (invalid_begin(token))
    {
        data->err = 1;
        return (1);
    }
    while (is_metecharacter(token->type) == 0)
        token = token->next;
    /// while non metecharacter token go to next node, if node = metachar
    /// check if it is the last node, if yes ==>disp err of `newline'. no ==> stop
    if (token->next == NULL)
    {
        if (invalid_end(token))
        {
            data->err = 1;
            return (1);
        }
    }
    return (0);
}

//// SYNTAX CHECKER : return a tokenzed linked list in seccuss;
/// Check For the first node; if it is an operator : generate error.
t_tokens    *syntax_checker(t_data *data)
{
    t_tokens    *ptr;

    ptr = data->token;
    if (check_first_end(data))
        return (ptr);
    while (data->token != NULL)
    {
        if (data->token->type == EXPAND_)
            expand_var(data);
        else if (data->token->type == SQUOTE || data->token->type == DQUOTE)
        {
            if (quotes_syntax(data))
                return (ptr);
        }
        // else if (data->token->type == PIPE)
        // {
        //     if (check_pipe (data))
        //         return (ptr);
        // }
        else if (data->token->type == REDOUT || data->token->type == APPEND)
        {
            if (check_rederections (data))
                return (ptr);
        }
        data->token  = data->token->next;
    }
    // printf("Checked by Success.\n\n");
    return (ptr);
}