/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/06 16:42:29 by ahammout         ###   ########.fr       */
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
    REDIN = '<',
    REDOUT = '>',
    APPEND = -124,
    HEREDOC = -120,
    PIPE = '|',
    EXPAND_ = '$',
    KEYWORD = -1,
};

// typedef struct  s_var
// {
//     char    *name;
//     char    *value;
// }               t_var;


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
    t_tokens    *token;
    int         err;
}               t_data;

        ///////// Minshell function principal //////////

int         minishell(t_data *data);

        /////////// LEXER //////////////

t_tokens    *lexer (t_data *data);
int         quotes (t_data *data, char *buff, char quote);
int         expand (t_data *data, char *buff);
int         is_escap (char c);
int         keyword (t_data *data, char *buff);
int         operator (t_data *data, char *buff, int type);
void        optype (int size, int type, t_tokens *token);
int         is_space_or_tab(char *buffer);
void        init_list(t_data *data);
void        add_new_node (t_data *data);

        //////// SYNTAX CHECKER ///////////
t_tokens    *syntax_checker (t_data *data);
int         check_quotes(char *lexem, int type);
void        abs_syntax(t_data *data, int lexem_len, int n_quotes);
void        generate_err(t_data *data, char *input, char *err);
int         expander (t_data *data, char *buff);

        //////////// TOOLS ///////////////
int         non_white(char *str);
void        free_data (t_data *data);
void        exit_error (t_data *data, int option, char *err);
char        **ft_2strdup (char **str);
void        display_list (t_tokens *token);

// Tokens = command ; file ; sentence ; Operators ; 
// command > sentence > Operator > file

// Dif bet > & >> 
#endif
