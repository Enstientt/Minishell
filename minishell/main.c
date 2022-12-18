    /////// WAITING SIGNALS [ Ctrl-Z, Ctrl-D, Ctrl-C, Ctrl-\ ] //
    /////// When press on of the keys with Ctrl, it's reffers ///
    /////// to certain signal need to hadle it //////////////////


#include "minishell.h"

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$> ");
        lexer(line);
        // printf("%s", line);
    }
}