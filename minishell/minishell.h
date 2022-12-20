#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<stdlib.h>
#include"libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

/* add list of tokens characters*/

enum{
    SQUOTE = '\'',
    DQUOTE = '\"',
    REDIN = '<',
    REDOUT = '>',
    

}

/* Token list : first var is Lexem = "data"
                second var is type = "token type"
                third var = "Next node"
*/

typedef struct  s_token
{
    char            *lex;
    int             type;
    struct t_token  *next;
}               t_token;

int lexer(char *buffer);

#endif