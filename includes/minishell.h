/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/26 01:32:07 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h> 
#include"../libft/libft.h"
#include"../get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>

enum
{
    SQUOTE = '\'',
    DQUOTE = '\"',
    REDIN = '<',
    REDOUT = '>',
    APPEND = -124,
    HEREDOC = -120,
    PIPE = '|',
    EXPAND_ = '$',
    SEMICOLONE = ';',
    AND = '&',
    EMPTY = 0,
    KEYWORD = -1,
};

typedef struct  s_reference
{
    int i;
    int j;
    int l;
}               t_reference;

typedef struct  s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}               t_env;

typedef struct  s_tokens
{
    char                *lex;
    int                 type;
    int                 lenght;
    struct s_tokens     *next;
    struct s_tokens     *prev;
}               t_tokens;

typedef struct  s_exec
{
    char **str;
    char *flg;
    int in_file;
    int out_file;
    struct s_exec *next;
}               t_exec;

typedef struct  s_data
{
    char        *buffer;
    char        **envp_;
    t_env       *env;
    t_tokens    *tokens;
    t_exec      *cmds;
    int         err;
}               t_data;


//---------------------------------/ PARSING PART /--------------------------------------//
void            parse_line(t_data *data);

//////////////////////////////// LEXER ///////////////////////////////////////////

t_tokens        *lexer(t_data *data);    
int             is_keyword(char c);
int             is_quoted(char c);
int             is_whitespace(char c);
int             is_special_op(char c);
int             is_metecharacter(int type);
int             white_space(t_data *data, char *lexem);
int             quotes(t_data *data, char *lexem, char type);
int             expand(t_data *data, char *lexem);
int             keyword(t_data *data, char *lexem);
int             special_op(t_data *data, char *lexem, int type);
void            optype (int size, int type, t_tokens *token);
void            split_token(t_data *data);
int             q_keyword(t_data *data, char *lexem);
void            init_tokens_list(t_data *data);
void            create_new_node(t_data *data, int *add_node);
void            add_new_node(t_data *data);
void            free_tokens_list(t_data *data);

///////////////////////////////// ENVIRONMENT /////////////////////////////////

void            set_environment(t_data *data, char **envp);
void            init_env_list(t_data *data);
void            add_node(t_data *data, int *new_node);
int             fill_name(t_data *data, char *envp);
int             fill_value(t_data *data, char *envp);
void            free_env_list(t_data *data);

///////////////////////////////// SYNTAX ANALYZER //////////////////////////////

t_tokens        *syntax_analyzer(t_data *data);
int             analyze_begin_end(t_data *data);
int             analyze_pipe(t_data *data);
int             analyze_redirections(t_data *data);
int             analyze_quotes(t_data *data);
int             quotes_syntax(char *lexem, int type);
void            abs_syntax(t_data *data, int lexem_len, int n_quotes);
int             analyze_begin(t_tokens *token);
int             analyze_end(t_tokens *token);
int             analyze_file(t_tokens *token);
    
///////////////////////////////// EXPANDER //////////////////////////////////////

t_tokens        *expander(t_data *data);
void            lexem_matching(t_data *data);
int             handle_dolar_sign(char *lexem, char **pids);
void            expandable(t_data *data, char *lexem, char *pids);
void            unexpandable(t_data *data, char *lexem, char *pids);
void            non_param(t_data *data, char *lexem, char *str_pid);
char            *get_var(t_data *data, char *lexem);
char            *get_value(t_data *data, char *var);
void            var_exist(t_data *data, char *pids, char *value);
void            var_not_exist(t_data *data, char *lexem, char *pids);
int             update_size(char *lexem, char *pids, char *value);
int             update_size_(char *lexem, char *pids);

/////////////////////////////////// PARSER //////////////////////////////////

t_exec          *parser(t_data *data);
char            **get_cmd_args(t_data *data);
int             get_size(t_data *data);
void            init_cmds_list(t_data *data);
void            next_cmd(t_data *data);
int             is_redirection(int type);
int             redirection_handler(t_data *data);
int             check_redirection(t_data *data);
int             redin_handler(t_data *data);
int             redout_handler(t_data *data);
int             append_handler(t_data *data);
int             heredoc_handler(t_data *data);
void            free_cmds_list(t_data *data);

/////////////////////////////////// TOOLS //////////////////////////////////

void            exit_error(t_data *data, char *err);
void            free_data(t_data *data);
int             generate_error(t_data *data, char *error);
char            **ft_2strdup(char **str);
int             white_check(char *str);
void            display_tokens(t_tokens *token);
void            display_table(char **dstr);
void            display_cmds(t_exec *cmds);
void            display_environment(t_data *data);

#endif
