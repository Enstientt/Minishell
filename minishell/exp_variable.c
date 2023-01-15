#include"minishell.h"







// int expander_var (t_data *data, char *buff)
// {
//     int     d;
//     int     i;
//     char    *var;
//     char    *value;

//     d = 0;
//     var = NULL;
//     while (buff[d] == EXPAND_)
//         d++;
//     if (buff[d] != ' ' && buff[d] != '\t')
//     {
//         // if (buff[i] == '?')
//         //     get_exit_status(data, buff + i);
//         var = get_var (data, buff + d);
//         value = get_value (data, var);
//         if (value != NULL)
//             merge(data, value);
//         /// if variable not exist.
//         /// don't dispay it
//     }
//     free  (var);
//     return (i);
// }


/// EX : This is the PWD var : $PWD from the env.
void    merge(t_data *data, char *value)
{
    char    *temp;
    int     i;
    int     j;
    int     v;

    temp = data->token->lex;
    free(data->token->lex);
    exit (0);
    printf("NEW SIZE :%d \n", size_update(data, temp, value));
    data->token->lex = malloc(sizeof(char) * size_update(data, temp, value));
    if (!data->token->lex)
    {
        free(temp);
        exit_error(data, 2, "Minishell: Allocation failed.");
    }
    i = 0;
    j = 0;
    v = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (temp[i] != ' ' && temp[i] != '\t' &&  temp[i] != '\0' && temp[i] != data->token->type)
                i++;
            while (value[v])
                data->token->lex[j++] = value[v++];
        }
        if (temp[i] != '\0')
            data->token->lex[j++] = temp[i++];
    }
    data->token->lex[j] = '\0';
}

int non_stopable(char c)
{
    if (c != ' ' && c != '\t' && c != '\0'
        && (!ft_isdigit(c) && !ft_isalpha(c))
        && c != '_')
        return (1);
    return (0);
}

int size_update(char *temp, char *dolars, char *value)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (non_stopable(temp[i]))
                i++;
        }
        if (temp[i] != '\0')
        {
            len++;
            i++;
        }
    }
    printf("CHARACTERS: %d\n", len);
    printf("VAR VALUE: %zu\n", ft_strlen(value));
    printf("PID VALUES: %zu\n", ft_strlen(dolars));
    return (len + ft_strlen(value) + ft_strlen(dolars));
}

void    var_exist(t_data *data, char *dolars, char *value)
{
    char    *temp;

    temp = ft_strdup(data->token->lex);
    free(data->token->lex);
    printf("The new size: %d\n", size_update(temp, dolars, value));
    exit (0);
    // data->token->lex = malloc (sizeof(char) * size_update(data, temp, dolars, value));
}

char    *get_value(t_data *data, char *var)
{
    int i;
    int j;
    int v;

    i = 0;
    if (var == NULL)
        return (0);
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
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0')
    {
        if (buff[i] == '_')
            return (NULL);
        i++;
    var = malloc(sizeof(char) * i);
    if (!var)
        exit_error(data, 2, "Minishell: Allocation failed.");
    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' &&  buff[i] != '\0')
    {
        var[i] = buff[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}

// Expand$$$$$HOME
void    exp_var(t_data *data, char *buff, char *dolars)
{
    char    *var;
    char    *value;
    int     i;
    // int     len;

    i = 0;
    // len = 0;
    dolars = 0;
    while (buff[i] == EXPAND_)
        i++;
    var = get_var(data, buff + i);
    value = get_value(data, var);
    // if variable exist.
    if (value)
        var_exist(data, dolars, value);
    else
        var_not_exist(data, dolars);
    printf("variable name: %s\n", var);
    exit (0);
}