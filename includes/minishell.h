/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:27 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/26 00:12:54 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include<syslimits.h>

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
        WHITE = -2,
};

int	exitS;

typedef struct  s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}               t_env;

typedef struct s_exec
{
	char			**str;
	char			*flg;
	int				in_file;
	int				out_file;
	struct s_exec	*next;
}	t_exec;

typedef struct  s_reference
{
    int     i;
    int     j;
    int     l;
}               t_reference;

typedef struct  s_tokens
{
    char                *lex;
    int                 type;
    int                 lenght;
    struct s_tokens     *next;
}               t_tokens;

typedef struct s_vars
{
	t_exec	*tmp;
	int		*pids;
	int		status;
	int		*std;
	int		i;
}				t_vars;

typedef struct s_cmd
{
	char			*str;
	t_tokens		type;
	bool			opr;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_pipe
{
	int		p_c;
	int		**p_fd;
}	t_pipe;

typedef struct  s_data
{
    char        **envp_;
    char        *buffer;
    t_tokens    *tokens;
    t_env       *env;
    t_pipe      *pipex;
    t_cmd       *cmd;
    int         err;
    t_exec      *exec;
    char	path[PATH_MAX];
}               t_data;

    /////////////////////////////// execution /////////////////////////////////////
void	ft_echo(t_exec	*exec);
int     identify_builtin(t_data *data, t_exec	*cmd);
void	ft_cd(t_data	*data);
int     check_pipes(t_exec	*exec);
void	handle_loop(t_vars	pipe, int her_file, t_data	*data);
int     *save_std(void);
int     **pipe_gener(int count);
void	redirect_inpipes(t_exec	*tmp, int status, t_data	*data, int i);
void	close_fd(t_data	*data);
void	handle_loop(t_vars	pipe, int her_file, t_data	*data);
int     redirect_pipes(t_exec *tmp, int file_, int i, t_data *data);
void	exec_pipes(t_exec *exc, t_data *data, int file_, char **envp_);
void	pipe_exe(int *pids, t_data	*data, t_exec *tmp, int i);
void	restore_parent(int	*stds, int status, int	*pids, t_data	*data);
void	handle_fds(t_data *data, int i);
void	ft_exit(t_exec	*cmd);
    /////////////////////////////// PARSING PART /////////////////////////////////////

t_tokens        *parse_line(t_data *data);

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
void            init_list(t_data *data);
void            create_new_node(t_data *data, int *add_node);
void            add_new_node(t_data *data);

///////////////////////////////// ENVIRONMENT /////////////////////////////////

void            set_environment(t_data *data);
void            add_node(t_data *data, int *new_node);
int             fill_name(t_data *data, char *envp_);
int             fill_value(t_data *data, char *envp_);
void            display_environment(t_data *data);

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
 
 /////////////////////////////////// UTILS //////////////////////////////////
void            exit_error(t_data *data, int option, char *err);
void            free_data(t_data *data);
char            **ft_2strdup(char **str);
int             white_check(char *str);
void            display_list (t_tokens *token);
void            display_table(char **dstr);

#endif
