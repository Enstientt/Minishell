/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/27 19:13:25 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    APPEND = -124,
    HEREDOC = -120,
    SEPERATOR = ';',
    PIPE = '|',
    EXPAND_ = '$',
    KEYWORD = -1,
};

typedef struct  s_var
{
    char    *name;
    char    *value;
}               t_var;

typedef struct  s_env
{
    t_var   var;
}               t_env;


typedef struct  s_tokens
{
    char            *lex;
    int             type;
    int             lenght;
    struct s_tokens  *next;
}               t_tokens;

typedef struct  s_data
{
    char        *buffer;
    char        **envp_;
    t_env       *env;
    t_tokens    *tokens;
}               t_data;

int     lexer(t_data *data);
int     quotes(t_data *data, char *buff, t_tokens *tmp, char quote);
int     escap(t_data *data, char *buff, t_tokens *tmp);
int     is_escap(char c);
int     keyword(t_data *data, char *buff, t_tokens *tmp);
int     operator(t_data *data, char *buff, t_tokens *tmp, int type);
void    optype(int size, int type, t_tokens *tmp);
int     add_new_node(t_data *data, t_tokens *tmp);
void    free_data(t_data *data);
void    free_tmp(t_tokens *to_free);
void    exit_error(t_data *data, int option, char *err);
void    gen_error(t_data *data, char *input, char *err);
void    display_list(t_data *data);

// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif
