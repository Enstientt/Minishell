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
    KEYWORD = -1,
};

typedef struct  s_tokens
{
    char            *lex;
    int             type;
    struct s_tokens  *next;
}               t_tokens;

typedef struct  s_data
{
    char        *buffer;
    t_tokens    *tokens;
}               t_data;

int lexer(t_data *data);
int sentence(t_data *data, char *buff, t_tokens **tmp, char quote);
int is_quoted(char c);
int add_new_node(t_data *data, t_tokens *token);
int free_list(t_data *data);
int exit_error(t_data *data, int option, char *err);
void    display_list(t_data *data);

// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif