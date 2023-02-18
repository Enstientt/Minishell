/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:12:53 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 16:39:14 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    display_environment(t_data *data)
{
    t_env   *head;
    int     index;

    head = data->env;
    index = 0;
    while (head != NULL)
    {
        printf ("---------------------  Node %d  ---------------------\n\n", index);
        printf(" *Name: %s\n", head->name);
        printf (" *Value: %s\n\n", head->value);
        index++;
        head = head->next;
    }
}

int fill_value(t_data *data, char *envp_)
{
    t_reference ref;

    ref.l = 1;
    ref.j = 1;
    ref.i = 0;
    while (envp_[ref.l])
        ref.l++;
    data->env->value = malloc(sizeof (char) * (ref.l - 1));
    if (!data->env->value)
        exit_error (data, 1, "Minishell: Allocation failed.");
    while (envp_[ref.j])
        data->env->value[ref.i++] = envp_[ref.j++];
    data->env->value[ref.i] = '\0';
    return (ref.j);
}

int fill_name(t_data *data, char *envp_)
{
    t_reference ref;

    ref.l = 0;
    ref.i = 0;
    ref.j = 0;
    while (envp_[ref.l] != '=')
        ref.l++;
    data->env->name = malloc (sizeof (char) * ref.l);
    if (!data->env->name)
        exit_error (data, 1, "Minishell: Allocation failed.");
    while (envp_[ref.j] != '=')
        data->env->name[ref.i++] = envp_[ref.j++];
    data->env->name[ref.i] = '\0';
    return (ref.j);
}

void    add_node(t_data *data, int *new_node)
{
    t_env   *node;
    
    node = NULL;
    if (*new_node)
    {
        node = malloc(sizeof(t_env));
        if (!node)
            exit_error (data, 1, "Minishell: Allocation failed.");
        node->next = NULL;
        data->env->next = node;
        data->env = data->env->next;
    }
    else
        *new_node = 1;
}

void    set_environment(t_data *data)
{
    t_reference ref;
    t_env       *head;
    int         new_node;
    
    ///////////////// INIT ENV LIST /////////////////////
    data->env = malloc (sizeof (t_env));
    if (!data->env)
        exit_error(data, 1, "Minishell: Allocation failed.");
    data->env->next = NULL;

    //////////////// ENVP_ MATCHING /////////////////////
    head = data->env;
    ref.i = 0;
    ref.j = 0;
    new_node = 0;
    while (data->envp_[ref.i])
    {
        add_node(data, &new_node);
        ref.j = 0;
        while (data->envp_[ref.i][ref.j])
        {  
            ref.j += fill_name(data, data->envp_[ref.i] + ref.j);
            ref.j += fill_value(data, data->envp_[ref.i] + ref.j);
        }
        ref.i++;
    }
    data->env = head;
}