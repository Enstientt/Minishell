/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes
/// Option : option with single op-Character / many op-characters

#include "minishell.h"

/// REDOUT : INVALID FILE FORMAT ==> INVALID FILES NAME : && , || , 
// PIPE:   INVALID FORMAT: || .
int check_pipe (t_data *data)
{
    if (data->token->lenght > 1 || data->token->next == NULL)
    {
        printf("Minishell: syntax error near unexpected token `%c'\n", data->token->lex[0]);
        data->err = 1;
        return (1);
    }
    return (0);
}

int is_metecharacter(int type)
{
    if (type == REDIN || type == REDOUT
        || type == APPEND || type == HEREDOC
        || type == PIPE)
        return (1);
    return (0);
}

int check_redirections (t_data *data)
{
    t_tokens    *token;

    token = data->token;
    /// Check The file Name : a non valid fie whose begin with a metacharacter
    if (token->lenght > 2)
        data->err = 1;
    token = token->next;
    if (token == NULL)
    {
        printf("Minishell: syntax error near unexpected token `newline'\n");
        data->err = 1;
        return (1);
    }
    else if (invalid_file(token))
    {
        data->err = 1;
        return (1);
    }
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
    while (is_metecharacter(token->type) == 0 && token->next != NULL)
        token = token->next;
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

/// pipe: ehco "put this ono the file" > file | cat -e file | ls -l
t_tokens    *syntax_checker(t_data *data)
{
    t_tokens    *ptr;

    ptr = data->token;
    if (check_first_end(data))
        return (ptr);
    while (data->token != NULL)
    {
        if (data->token->type == KEYWORD)
            check_keyword(data);
        else if (data->token->type == SQUOTE || data->token->type == DQUOTE)
        {
            if (quotes_syntax(data))
                return (ptr);
        }
        else if (data->token->type == PIPE)
        {
            if (check_pipe (data))
                return (ptr);
        }
        else if (data->token->type == REDOUT || data->token->type == APPEND)
        {
            if (check_redirections (data))
                return (ptr);
        }
        data->token  = data->token->next;
    }
    // printf("Checked by Success.\n\n");
    return (ptr);
}