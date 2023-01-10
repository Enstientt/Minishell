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

int expand (t_data *data, char *buff)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    data->token->lex = malloc (sizeof(char) * len);
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
    {
        data->token->lex[i] = buff[i];
        i++;
    }
    data->token->lex[i] = '\0';
    data->token->type = EXPAND_;
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

// echo "" | ls -l | touch file | echo "This on The file" > file
// "union quoted "union quoted "Union Quoted "Union quoted""""    [W]
//  echo "hello, World "Here is again "Expand this $PWD UNION  """""   [W]

int non_empty(char *buff, char type)
{
    int i;

    i = 0;
    while (buff[i] )
    {
        if (buff[i] == type)
            return (1);
        i++;
    }
    return (0);
}

int quoted_size(char *buff)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while (buff[len])
    {
        if (end_of_quote(buff + len))
            return (len);
        len++;
    }
    return (len);
}

int quotes(t_data *data, char *buff, char type)
{
    int i;
    int j;

    i = 0;
    j = 0;
    data->token->lex = malloc(sizeof(char) * quoted_size(buff));
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (buff[i] == type)
        data->token->lex[j++] = buff[i++];
    while (buff[i] != type)
        data->token->lex[j++] = buff[i++];
    while (buff[i] == type)
        data->token->lex[j++] = buff[i++];
    data->token->lex[j] = '\0';
    data->token->type = type;
    return(i);
}