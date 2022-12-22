
#include "minishell.h"

int main(void)
{
    t_data  data;
    size_t  len;

    data.buffer = NULL;
    len = 0;
    while (1)
    {
        //// Reading the input line
        while (len == 0)
        {
            data.buffer = readline("minishell$> ");
            len = ft_strlen(data.buffer);
        }
        data.token = malloc(sizeof(t_tokens));
        data.token->lex = data.buffer;
        data.token->next = NULL;
        new_node(&data);
        while (data.token != NULL)
        {
            printf("%s\n", data.token->lex);
            data.token = data.token->next;
        }
        free_node(&data);
        while (data.token != NULL)
        {
            printf("%s\n", data.token->lex);
            data.token = data.token->next;
        }

        // lexer(&data);
        break;
        
    }
}