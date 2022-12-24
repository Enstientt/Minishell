
#include "minishell.h"

int main(void)
{
    char    *input;
    t_data  data;

    data.buffer = NULL;
    while (1)
    {
        //// Reading the input line
        while (!data.buffer)
        {
            input = readline("minishell$> ");
            data.buffer = ft_strdup(input);
        }
        /// Lexer : part one-> tokonizing the buffer
        lexer(&data);

        /// Lexer analyzer : generate errors / generate a valid linked list.
    }
}