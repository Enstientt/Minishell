/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/19 23:39:55 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_data(t_data *data)
{
    free(data->buffer);
    free_env_list(data);
    free_tokens_list(data);
    free_cmds_list(data);
}

void    exit_error(t_data *data, char *err)
{
    free(data->buffer);
    free(data->envp_);
    free_tokens_list(data);
    printf("%s\n", err);
    exit(EXIT_FAILURE);
}
char    **ft_2strdup(char **tab1)
{
    int len;
    int i;
    char    **tab2;
    
    len = 0;
    i = 0;
    while(tab1[len])
        len++;
    tab2 = malloc(sizeof(char*) * len);
    while (tab1[i])
    {
        tab2[i] = ft_strdup(tab1[i]);
        i++;
    }
    tab2[i] = NULL;
    return (tab2);
}

int white_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isprint(str[i]))
            return (1);
        i++;
    }
    return (0);
}

void    display_table(char **dstr)
{
    int i;

    i = 0;
    while (dstr[i])
    {
        printf ("Line[ %d ]: %s\n",i, dstr[i]);
        i++;
    }
}
