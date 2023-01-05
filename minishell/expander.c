#include "minishell.h"

int size_update(t_data *data, char *temp, char *value)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t' && temp[i] != '\0' && temp[i] != data->token->type)
                i++;
        }
        if (temp[i] != '\0')
        {
            len++;
            i++;
        }
    }
    return (len + ft_strlen(value));
}

/// EX : This is the PWD var : $PWD from the env.
void    merge(t_data *data, char *value)
{
    char    *temp;
    int     i;
    int     j;
    int     v;

    temp = data->token->lex;
    free(data->token->lex);
    data->token->lex = malloc(sizeof(char) * size_update(data, temp, value));
    if (!data->token->lex)
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
            while (temp[i] != ' ' && temp[i] != '\t' && temp[i] != data->token->type)
                i++;
            while (value[v])
                data->token->lex[j++] = value[v++];
        }
        data->token->lex[j++] = temp[i++];
    }
    data->token->lex[j] = '\0';
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
        {
            // free(var);
            return (data->envp_[i] + j);
        }
        i++;
    }
    return (0);
}

char    *get_var(t_data *data, char *buff)
{
    int     i;
    char    *var;

    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != data->token->type)
        i++;
    var = malloc(sizeof(char) * i);
    if (!var)
        exit_error(data, 2, "Minishell: Allocation failed.");
    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != data->token->type)
    {
        var[i] = buff[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}

// EX = $$$PATH
int expander(t_data *data, char *buff)
{
    int     i;
    int     j;
    int     d;
    char    *var;
    char    *value;

    j = 0;
    d = 0;
    var = NULL;
    while (buff[d] == EXPAND_)
        d++;
    i = d;
    if (d == 1 && buff[i] != ' ' && buff[i] != '\t')
    {
        var = get_var(data, buff + i);
        value = get_value(data, var);
        if (value != NULL)
            merge(data, value);
        /// if variable not exist.
        /// don't dispay it
    }
    free(var);
    return (i);
}