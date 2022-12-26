#include"minishell.h"

void    optype(int size, int type, t_tokens *tmp);

void    optype(int size, int type, t_tokens *tmp)
{
    if (size == 1 && type == REDOUT)
        tmp->type = REDOUT;
    else if (size > 1 && type == REDOUT)
        tmp->type = APPOUT;
    else if (size == 1 && type == REDIN)
        tmp->type = REDIN;
    else if (size > 1 && type == REDIN)
        tmp->type = APPIN;
    else if (type == PIPE)
        tmp->type = PIPE;
    else if (type == SEPERATOR)
        tmp->type = PIPE;
    else if (type == VARIABLE_)
        tmp->type = VARIABLE_;
}

int operator(t_data *data, char *buff, t_tokens *tmp, int type)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (buff[len] == type)
        len++;
    tmp->lex = malloc (sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (buff[i] == type)
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    optype(len, type, tmp);
    return (i);
}

int keyword(t_data *data, char *buff, t_tokens *tmp)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = KEYWORD;
    return (i);
}

int escap(t_data *data, char *buff, t_tokens *tmp)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (is_escap(buff[len]))
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (is_escap(buff[i]))
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = ESCAP;
    return (i);
}

int quotes(t_data *data, char *buff, t_tokens *tmp, char quote)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;

    // COUNTING THE SIZE FOR ALLOCATION DY
    while (buff[len] == quote)
        len++;
    while (buff[len] != quote && buff[len] != '\0')
        len++;
    while (buff[len] == quote)
        len++;
    tmp->lex = malloc(sizeof(char) * len);
    if (!tmp->lex)
        exit_error(data, 2, "Minishell: Allocation failed");
    while (buff[i] == quote)
        tmp->lex[j++] = buff[i++];
    while (buff[i] != quote && buff[i] != '\0')
        tmp->lex[j++] = buff[i++];
    while (buff[i] == quote)
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = quote;
    return(i);
}

