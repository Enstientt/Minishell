
#include "minishell.h"

int main(void)
{
    char    *buffer;
    size_t  len;

    buffer = NULL;
    len = 0;
    while (1)
    {
        //// Reading the input line
        while (len == 0)
        {
            buffer = readline("minishell$> ");
            len = ft_strlen(buffer);
        }
        printf("buffer= %s      size= %zu\n", buffer, len);
        lexer(buffer); 
        break;
        
    }
}