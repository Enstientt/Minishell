/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/01 13:24:07 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
    free(data->buffer);
    data->buffer = NULL;
    while (data->token != NULL)
    {
        free(data->token->lex);
        free(data->token);
        data->token = data->token->next;
    }
}

void exit_error(t_data *data, int option, char *err)
{
    if (option == 1)
    {
        free(data->buffer);
        printf("%s\n", err);
    }
    else if (option == 2)
    {
        free(data->buffer);
        while (data->token != NULL)
        {
            free(data->token->lex);
            free(data->token);
            data->token = data->token->next;
        }
    }
    exit(EXIT_FAILURE);
}
