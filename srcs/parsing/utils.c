/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:22:33 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void    free_data(t_data *data)
{
    while (data->tokens != NULL)
    {
        free(data->tokens->lex);
        free(data->tokens);
        data->tokens = data->tokens->next;
    }
}

void exit_error(t_data *data, int free_tokens, char *err)
{
    if (free_tokens)
    {
        while (data->tokens != NULL)
        {
            free(data->tokens->lex);
            free(data->tokens);
            data->tokens = data->tokens->next;
        }
    }
    free(data->buffer);
    free(data->envp_);
    
        printf("%s\n", err);
    exit(EXIT_FAILURE);
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
