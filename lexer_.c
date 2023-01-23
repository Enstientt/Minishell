#include"minishell.h"

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

int expand(t_data *data, char *buff)
{
    int i;
    int j;
    int len;
    int content;

    i = 0;
    j = 0;
    len = 0;
    content = 0;
    while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
    {
        if (buff[len] != EXPAND_)
            content++;
        if (content > 0 && buff[len] == EXPAND_)
            break;
        len++;
    }
    content = 0;
    data->token->lex = malloc (sizeof(char) * len);
    if (!data->token->lex)
        exit_error (data, 2, "Minishell: ALlocation failed.");
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
    {
        if (buff[i] != EXPAND_)
            content++;
        if (content > 0 && buff[i] == EXPAND_)
            break;
        data->token->lex[j++] = buff[i++];
    }
    data->token->lex[j] = '\0';
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
    while (non_operator(buff[len]) && buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
        len++;
    data->token->lenght = len;
    data->token->lex = malloc(sizeof(char) * len);
    if (!data->token->lex)
        exit_error(data, 2, "Minishell: Allocation failed.");
    while (non_operator(buff[i]) && buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
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