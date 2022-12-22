#include"minishell.h"

int exit_error(t_data *data, int option, char *err)
{
    /// FREE JUST THE BUFFER && DISPLAY ERROR
    if (option == 1)
    {
        free(data->buffer);
        printf("%s\n", err);
        exit(EXIT_FAILURE);
    }
    return (0);
    
}

/// give the original list
int free_node(t_data *data)
{
    while (data->token->next != NULL)
    {
        free(data->token);
        data->token = data->token->next;
    }
    return (0);
}

int new_node(t_data *data)
{
    t_tokens    *token;

    token = malloc(sizeof(t_tokens));
    if (!token)
        exit_error(data, 1, "Malloc: allocation failed.");
    token->next = NULL;
    data->token->next = token;
    return (0);
}