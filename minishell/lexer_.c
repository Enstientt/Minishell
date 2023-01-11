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
}

//// Function bellow return the size of lexem if option equal to 0 
///  | otherwise fill the lexem and return index [index = lenght].
int operator (t_data *data, char *buff, int type)
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
    while (non_operator(buff[len]) && buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
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

int quoted_size (char *buff, char type)
{
    int i;
    int q;

    i = 0;
    q = 0;
    while (q < 2)
    {
        if (buff[i] == type)
            q++;
        i++;
    }
    return (i);
}
/// EX = "hello"

int quotes(t_data *data, char *buff, char type)
{
    int i;
    int j;
    int q;

    i = 0;
    j = 0;
    q = 0;
    data->token->lex = malloc(sizeof(char) * quoted_size(buff, type));
    while (q < 2)
    {
        if (buff[i] == type)
            q++;
        data->token->lex[j++] = buff[i++];
    }
    data->token->lex[j] = '\0';
    data->token->type = type;
    return (i);
}