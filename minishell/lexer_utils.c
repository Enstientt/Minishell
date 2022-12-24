#include "minishell.h"

int is_quoted(char c)
{
    if (c != '>' && c != '<' && c != '|' 
        && c != ';' && c != '\0' && c != '\'' 
        && c != '\"')
        return (1);
    return (0); 
}

void    display_list(t_data *data)
{
    int n;

    n = 0;
    // DISPLAY THE LIST 
    while (data->tokens != NULL)
    {
        printf("---- Node %d ----\nLexeme: %s\nType: %d\n\n", n, data->tokens->lex, data->tokens->type);
        n++;
        data->tokens = data->tokens->next;
    }
}