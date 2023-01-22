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
    char    *dolars;
    char    *pid;

    d = 0;
    pid = ft_itoa(getppid());
    while (buff[d] == EXPAND_)
        d++;
    dolars = expand_dolars(buff, pid);
    if (d % 2 != 0 && buff[d] != '\0')
    {
        if (is_silent(buff[d]))
            expand_silent (data, dolars, 1);
        else if (!is_silent(buff[d]))
            exp_var(data, buff, dolars);
    }
    else if (d % 2 == 0 && buff[d] != '\0')
        expand_silent (data, dolars, 0);
    else
        non_param(data, dolars);
    free(dolars);
    return (0);


}