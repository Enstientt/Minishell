#include "minishell.h"

/// COIUNTING THE SIZE OF NEW LEXEME
int size_update(char *temp, char *value)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t')
                i++;
        }
        len++;
    }
    return (len + ft_strlen(value));
}

/// EX : This is the PWD var : $PWD from the env

void    merge(t_data *data, t_tokens *tmp, char *value)
{
    char    *temp;
    int     i;
    int     j;
    int     v;

    // temp = tmp->lex;
    // free(tmp->lex);
    printf("len: %zu\n", ft_strlen(tmp->lex));
        exit(0);
    printf("Old size: %zu\n", ft_strlen(temp));
    printf("New size: %d\n", size_update(temp, value));
    tmp->lex = malloc(sizeof(char) * size_update(temp, value));
    if (!tmp->lex)
    {
        free(temp);
        exit_error(data, 2, "Minishell: Allocation failed.");
    }
    /// FILL THE NEW LEXEM
    i = 0;
    j = 0;
    v = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t')
                i++;
            while (value[v])
                tmp->lex[j++] = value[v++];
        }
        tmp->lex[j++] = temp[i++];
    }
    free(temp);
}

// Get_value : Re
char    *get_value(t_data *data, char *var)
{
    int i;
    int j;
    int v;

    i = 0;
    while (data->envp_[i])
    {
        j = 0;
        v = 0;
        while (data->envp_[i][j] != '=')
        {
            if (data->envp_[i][j] != var[v])
                break;
            j++;
            v++;
        }
        if (data->envp_[i][j++] == '=')
            return (data->envp_[i] + j);
        i++;
    }
    return (0);
}

char    *get_var(t_data *data, char *buff)
{
    int     i;
    char    *var;

    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t')
        i++;
    var = malloc(sizeof(char) * i);
    if (!var)
        exit_error(data, 2, "Minishell: Allocation failed.");
    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t')
    {
        var[i] = buff[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}

// EX = $$$PATH
int expander(t_data *data, char *buff, t_tokens *tmp)
{
    int     i;
    int     j;
    int     d;
    char    *value;

    j = 0;
    d = 0;
    while (buff[d] == EXPAND_)
        d++;
    i = d;
    if (d == 1 && buff[i] != ' ' && buff[i] != '\t')
    {
        value = get_value(data, get_var(data, buff + i));
        printf("%s\n", value);
        if (value != NULL)
            merge(data, tmp, value);
        printf("%s\n", tmp->lex);
    }
    return (i);
}