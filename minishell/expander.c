#include "minishell.h"


// void    quotes_exp(char *buff);
// //// lexem = adfsfsfrfer$$$$$$@HOME.
// //// Buffer = $$$$$$@PWD

char    *expand_dolars(char *buff, char *pid)
{
    int     i;
    char    *dolars;

    i = 0;
    // if (buff[i] == EXPAND_ && buff[i + 1] != EXPAND_)
    //     return (NULL);
    dolars = ft_strdup("");
    while (buff[i] == EXPAND_)
    {
        if (buff[i] == EXPAND_ && buff[i + 1] == EXPAND_)
        {
            dolars = ft_strjoin (dolars, pid);
            i += 2;
        }
        else
        {
            dolars = ft_strjoin (dolars, "$");
            i++;
        }
    }
    return (dolars);
}

int expander (t_data *data, char *buff)
{
    int     d;
    int     i;
    char    *dolars;
    char    *var;
    char    *value;
    char    *pid;

    d = 0;
    i = 0;
    var = NULL;
    value = NULL;
    pid = ft_itoa(getppid());
    while (buff[d] == EXPAND_)
        d++;
    dolars = expand_dolars(buff, pid);
    if (d % 2 != 0 && buff[d] != '\0')
    {
        if (is_silent(buff[d]))
            expand_silent (data, dolars);
        else if (!is_silent(buff[d]))
            exp_var(data, buff, dolars);
    }
    else
        non_param(data, dolars);
    // else if (d % 2 != 0)
    return (0);
    // EVEN CASE
}