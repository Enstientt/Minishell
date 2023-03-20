/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:03:45 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/19 22:24:49 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    free_env_list(t_data *data)
{
    t_env   *tmp;

    while (data->env)
    {
        
        free(data->env->name);
        free(data->env->value);
        tmp = data->env;
        data->env = data->env->next;
        free (tmp);
    }
}

void    display_environment(t_data *data)
{
    t_env *head;
    int index;

    head = data->env;
    index = 0;
    while (head != NULL)
    {
        printf("---------------------  Node %d  ---------------------\n\n", index);
        printf(" *Name: %s\n", head->name);
        printf(" *Value: %s\n\n", head->value);
        index++;
        head = head->next;
    }
}