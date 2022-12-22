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
    ESCAP = '\\',
    OPTION = '-',
    REDIN = '<',
    REDOUT = '>',
    SEPERATOR = ';',
    PIPE = '|',
    DOLARS = '$',
};

typedef struct  s_tokens
{
    char            *lex;
    int             type;
    struct t_token  *next;
}               t_tokens;

typedef struct  s_data
{
    char        *buffer;
    t_tokens    *token;
}               t_data;

int lexer(t_data *data);
int sentence(t_data *data, int *index, char quote);


// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif