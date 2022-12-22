
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
        lexer(&data);
        break;
        
    }
}