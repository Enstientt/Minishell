#include"minishell.h"

void    non_param(t_data *data, char *dolars)
{
    int i;

    i = 0;
    free(data->token->lex);
    data->token->lex = malloc(sizeof (char) * ft_strlen(dolars));
    if (!data->token->lex)
        exit_error(data, 1, "Minishell: allocation failed.");
    while (dolars[i])
    {
        data->token->lex[i] = dolars[i];
        i++;
    }
    data->token->lex[i] = '\0';
}

int is_silent(char c)
{
    if (ft_isdigit(c) || c == '@')
        return (1);
    return (0);
}

int update_lexlen(char *temp, char *dolars, int exp)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (temp[i] != EXPAND_ && temp[i] != '\0')
    {
        i++;
        len++;
    }
    while (temp[i] == EXPAND_)
        i++;
    if (is_silent(temp[i]) && exp == 1)
        i++;
    while (temp[i++])
        len++;
    return (len + ft_strlen(dolars));
}

/// Allocate lexem string // put what behind $ sign in new lexem.

void    expand_silent (t_data *data, char *dolars, int exp)
{
    char    *temp;
    int     i;
    int     t;
    int     j;

    i = 0;
    j = 0;
    t = 0;
    temp = ft_strdup(data->token->lex);
    free(data->token->lex);
    data->token->lex = NULL;
    // printf("PIDS size: %zu\nNew size: %d\n", ft_strlen(dolars), update_lexlen(temp, dolars));
    data->token->lex = malloc(sizeof(char) * update_lexlen(temp, dolars, exp));
    while (temp[t] != EXPAND_ && temp[t] != '\0')
    {
        data->token->lex[i] = temp[t];
        i++;
        t++;
    }
    while (temp[t] == EXPAND_)
        t++;
    while (dolars[j])
    {
        if (dolars[j] != '$')
        {
            data->token->lex[i] = dolars[j];
            i++;
        }
        j++;
    }
    // is silent 
    if (is_silent (temp[t]) && exp == 1)
        t++;
    while (temp[t])
    {
        data->token->lex[i] = temp[t];
        i++;
        t++;
    }
    data->token->lex[i] = '\0';
    free(temp);
}

