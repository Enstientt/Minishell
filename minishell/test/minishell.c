#include"minishell.h"

int minishell(t_data *data)
{
    int buffer_size;

    buffer_size = 0;
    if (buffer_size)
        return (0);
    while (buffer_size == 0)
    {
        free(data->buffer);
        data->buffer = readline("minishell $> ");
        buffer_size = ft_strlen(data->buffer);
    }
    data->token = lexer(data);
    
    ////// CHECK THE SYNTAX : GENERATE ERRORS / GENERATE VALID COMMAND ///////
    /* 
        RETURN : SECCUES : + VALID SYNTAX ==> LINKED LIST[TOKENAZED].
                FAILURE : + INVALID SYNTAX ==> ERROR MESSAGE & EXIT FAILURE.
    */
    if (data->token)
    {
        data->token = syntax_checker (data);
        if (data->token)
        {
            printf("non Error\n");
            display_list(data->token);
            free_data(data);
        }
    }
    minishell(data);
    return (0);
}