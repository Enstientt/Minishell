/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 13:03:05 by ahammout         ###   ########.fr       */
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

int     lexer(t_data *data);
int     quotes(t_data *data, char *buff, t_tokens **tmp, char quote);
int     escap(t_data *data, char *buff, t_tokens **tmp);
int     is_escap(char c);
int     keyword(t_data *data, char *buff, t_tokens **tmp);
int     add_new_node(t_data *data, t_tokens *token);
void    free_data(t_data *data);
int     exit_error(t_data *data, int option, char *err);
void    display_list(t_data *data);

// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif
