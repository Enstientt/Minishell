#include"minishell.h"

int non_stopable(char c)
{
    if (ft_isalpha(c) || ft_isalpha(c) || c == '$' || c == '_')
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
    if (value)
        return (len + ft_strlen(dolars) + ft_strlen(value));
    return (len + ft_strlen(dolars));
}

void    var_not_exist (t_data *data, char *dolars)
{
    printf("Var not exist.\n");
    int     i;
    int     l;
    int     d;
    char    *temp;

    i = 0;
    l = 0;
    d = 0;
    temp = ft_strdup(data->token->lex);
    free(data->token->lex);
    data->token->lex = malloc(sizeof (char) * size_update(temp, dolars, NULL) - 1);
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (non_stopable(temp[i]))
                i++;
            while (dolars[d + 1])
                data->token->lex[l++] = dolars[d++];
        }
        if (temp[i] != '\0')
            data->token->lex[l++] = temp[i++];
    }
    data->token->lex[l] = '\0';
    free(temp);
}

void    var_exist(t_data *data, char *dolars, char *value)
{
    printf("Var exist.\n");
    int     i;
    int     d;
    int     v;
    int     l;
    char    *temp;

    i = 0;
    d = 0;
    l = 0;
    v = 0;
    temp = ft_strdup(data->token->lex);
    free(data->token->lex);
    printf("The new size: %d\n", size_update(temp, dolars, value) - 1);
    data->token->lex = malloc (sizeof(char) * size_update(temp, dolars, value) - 1);
    while (temp[i])
    {
        if (temp[i] == EXPAND_)
        {
            while (non_stopable(temp[i]))
                i++;
            while (dolars[d + 1])
                data->token->lex[l++] = dolars[d++];
            while (value[v])
                data->token->lex[l++] = value[v++];
        }
        else if (temp[i] != '\0')
            data->token->lex[l++] = temp[i++];
    }
    data->token->lex[l] = '\0';
    // printf("%s\n", data->token->lex);
    // exit (0);
    free(temp);
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
        if (data->envp_[i][j++] == '=' && !var[v] && !ft_isdigit(var[v] && !ft_isalpha(var[v]) && var[v] != '_'))
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
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\0' && (ft_isalpha(buff[i]) || ft_isdigit(buff[i])))
        i++;
    if (buff[i] == '_')
        return (NULL);
    var = malloc(sizeof(char) * i);
    if (!var)
        exit_error(data, 2, "Minishell: Allocation failed.");
    i = 0;
    while (buff[i] != ' ' && buff[i] != '\t' &&  buff[i] != '\0' && (ft_isalpha(buff[i]) || ft_isdigit(buff[i])))
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

    i = 0;
    while (buff[i] == EXPAND_)
        i++;
    var = get_var(data, buff + i);
    value = get_value(data, var);
    if (value)
        var_exist (data, dolars, value);
    else
        var_not_exist (data, dolars);
    free(var);
}