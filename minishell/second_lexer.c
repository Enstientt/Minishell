#include"minishell.h"

void    optype(int size, int type, t_tokens *tmp)
{
    if (size == 1 && type == REDOUT)
        tmp->type = REDOUT;
    else if (size > 1 && type == REDOUT)
        tmp->type = APPEND;
    else if (size == 1 && type == REDIN)
        tmp->type = REDIN;
    else if (size > 1 && type == REDIN)
        tmp->type = HEREDOC;
    else if (type == PIPE)
        tmp->type = PIPE;
    else if (type == SEPERATOR)
        tmp->type = PIPE;
    else if (type == EXPAND_)
        tmp->type = EXPAND_;
}

//// Function bellow return the size of lexem if option equal to 0 
///  | otherwise fill the lexem and return index [index = lenght].
int operator(char *buff, t_tokens *tmp, int type, int option)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;
    if (option == 0)
    {
        while (buff[len] == type)
            len++;
        tmp->lenght = len;
        return (len);
    }
    while (buff[i] == type)
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    optype(tmp->lenght, type, tmp);
    return (i);
}

int keyword(char *buff, t_tokens *tmp, int option)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    if (option == 0)
    {
        len = 0;
        while (buff[len] != ' ' && buff[len] != '\t' && buff[len] != '\0')
            len++;
        tmp->lenght = len;
        return (len);
    }
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = KEYWORD;
    return (i);
}

int escap(char *buff, t_tokens *tmp, int option)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    if (option == 0)
    {
        len = 0;
        while (is_escap(buff[len]))
            len++;
        tmp->lenght = len;
        return (len);
    }
    while (is_escap(buff[i]))
        tmp->lex[j++] = buff[i++];
    tmp->lex[j] = '\0';
    tmp->type = ESCAP;
    return (i);
}

int quotes(char *buff, t_tokens *tmp, char quote, int option)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = 0;

    // COUNTING THE SIZE FOR ALLOCATION DY
    if (option == 0)
    {
        while (buff[len] == quote)
            len++;
        while (buff[len] != quote && buff[len] != '\0')
            len++;
        while (buff[len] == quote)
            len++;
        return (len);
    }
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

