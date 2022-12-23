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
int free_list(t_data *data)
{
    while (data->tokens != NULL)
    {
        free(data->tokens);
        data->tokens = data->tokens->next;
    }
    return (0);
}

int add_new_node(t_data *data, t_tokens *token)
{
    t_tokens    *node;

    node = malloc(sizeof(t_tokens));
    if (!node)
        exit_error(data, 1, "Malloc: allocation failed.");
    node->next = NULL;
    token->next = node;
    return (0);
}