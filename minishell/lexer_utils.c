#include "minishell.h"



int is_escap(char c)
{
    if (c == '>' || c == '<' || c == '|' || c == ';' || c == '\0')
        return (0);
    return (1); 
}