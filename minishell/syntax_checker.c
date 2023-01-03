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

    first = 0;
    last = 0;
    while (lexem[first] == type)
        first++;
    i = first;
    while (lexem[i] != type)
        i++;
    while (lexem[i++] == type)
        last++;
    if (first != last)
        return (-1);
    return (first + last);
}

int syntax_quotes(t_data *data)
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
    while (data->token->lex[i] != data->token->type)
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
            if (syntax_quotes(data))
                return (ptr);
        // else if (data->token->type == ESCAP)
        //     escap_syntax(data);
        // else if (data->token->type == REDIN || data->token->type == APPEND 
        //     || data->token->type == HEREDOC || data->token->type == SEPERATOR)
        //     operator_syntax(data);
        data->token  = data->token->next;
    }
    // printf("Checked by Success.\n\n");
    return (ptr);
}