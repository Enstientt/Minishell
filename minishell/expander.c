#include "minishell.h"

void    merge(t_data *data, t_tokens *tmp, char *value);

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
        if (data->envp_[j++] == '=')
            return (data->envp_[i] + j);
        i++;
    }
    return (0);
}

int expander(t_data *data, char *buff, t_tokens *tmp)
{
    int     i;
    int     j;
    int     d;
    char    *var;
    char    *value;

    j = 0;
    while (buff[d] == EXPAND_)
        d++;
    i = d;
    if (d == 1 && buff[i] != ' ' && buff[i] != '\t')
    {
        while (buff[i] != ' ' && buff[i] != '\t')
            var[j++] = buff[i++];
        value = get_value(data, var);
        printf(value);
        // if (value != NULL)
        //     merge(data, tmp, value);
    }
    return (i);
}