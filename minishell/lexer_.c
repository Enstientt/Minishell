#include"minishell.h"

void    optype(int size, int type, t_tokens *token)
{
    if (size == 1 && type == REDOUT)
        token->type = REDOUT;
    else if (size > 1 && type == REDOUT)
        token->type = APPEND;
    else if (size == 1 && type == REDIN)
        token->type = REDIN;
    else if (size > 1 && type == REDIN)
        token->type = HEREDOC;
    else if (type == PIPE)
        token->type = PIPE;
    else if (type == SEPERATOR)
        token->type = PIPE;
}

//// Function bellow return the size of lexem if option equal to 0 
///  | otherwise fill the lexem and return index [index = lenght].
int operator(t_data *data, char *buff, int type)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (buff[len] == type)
        len++;
    data->token->lenght = len;
    data->token->lex = malloc(sizeof(char) * len);
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (buff[i] == type)
        data->token->lex[j++] = buff[i++];
    data->token->lex[j] = '\0';
    optype(data->token->lenght, type, data->token);
    return (i);
}

int keyword(t_data *data, char *buff)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    data->token->lenght = len;
    data->token->lex = malloc(sizeof(char) * len);
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
        data->token->lex[j++] = buff[i++];
    data->token->lex[j] = '\0';
    data->token->type = KEYWORD;
    return (i);
}

int escap(t_data *data, char *buff)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
        len = 0;
    while (is_escap(buff[len]))
        len++;
    data->token->lenght = len;
    data->token->lex = malloc(sizeof(char) * len);
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (is_escap(buff[i]))
        data->token->lex[j++] = buff[i++];
    data->token->lex[j] = '\0';
    data->token->type = ESCAP;
    return (i);
}

int quotes(t_data *data, char *buff, char quote)
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
    data->token->lex = malloc(sizeof(char) * len);
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (buff[i] == quote)
        data->token->lex[j++] = buff[i++];
    while (buff[i] != quote && buff[i] != '\0')
        data->token->lex[j++] = buff[i++];
    while (buff[i] == quote)
        data->token->lex[j++] = buff[i++];
    data->token->lex[j] = '\0';
    data->token->type = quote;
    return(i);
}