/// Keywords types: 1-file ; 2-command ; 3-sentence.

/// Quote : Double / Single quotes  & ESCAP
/// Option : option with single op-Character / many op-characters

#include "minishell.h"


void    generate_err(t_data *data, char *input, char *err)
{
    printf("Minishell: %s: %s", input, err);
    free(data->buffer);
    while (data->tokens != NULL)
    {
        free(data->tokens->lex);
        free(data->tokens);
        data->tokens = data->tokens->next;
    }
    exit(EXIT_FAILURE);
}

// Process 2 
// "Content is here"    |    [ "Content is here""       |      "Content is here ] Syntax error
void    syntax_quotes(t_data *data, t_tokens *tmp, t_tokens *to_free)
{
    int i;
    int first;
    int last;

    i = 0;
    first = 0;
    last = 0;
    while (tmp->lex[i])
    {
        while (tmp->lex[i++] == tmp->type)
            first++;
        while (tmp->lex[i] != tmp->type)
        {
            if (tmp->lex[i] == EXPAND_)
                i += expander(data, tmp->lex + i, tmp);
            i++;
        }
        while (tmp->lex[i] == tmp->type)
            last++;
        if (first != last)
        {
            free_tmp(to_free);
            generate_err(data, tmp->lex, "inclosed quotes");
        }
        /// get the absolute syntax of what between quotes;
        /// Arguments :
        /// data ==> struct of data,  tmp ==> the token with type |Quote|,  size of Lexeme.
        //abs_syntax(data, tmp, ft_strlen(tmp->lex));

        free(to_free);
    }
}


int syntax_checker (t_data *data)
{
    t_tokens    *tmp;
    t_tokens    *to_free;

    tmp = data->tokens;
    to_free = tmp;
    // while (tmp != NULL)
    // {
    //     if (tmp->type == SQUOTE || tmp->type == DQUOTE)
    //         syntax_quotes(data, tmp, to_free);
    //     else if (tmp->type == ESCAP)
    //         syntax_quotes(data, tmp, to_free);
    //     // else if (tmp->type == REDIN || tmp->type == APPEND || tmp->type == HEREDOC || tmp->type == SEPERATOR)
    //     //     operator_syntax(data, tmp, to_free);
    //     tmp  = tmp->next;
    // }
    // return (0);
    printf("%s\n", tmp->lex);
    exit(0);
}