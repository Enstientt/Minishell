/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_environemnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:58:36 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/26 23:21:52 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_env   *strToList(char **envp)
{
    t_env *env;
    t_env *tmp;
    int i;
    char **tmp2;

    i = 0;
    env = NULL;
    while (envp[i])
    {
        tmp = (t_env *)malloc(sizeof(t_env));
        tmp2 = ft_split(envp[i], '=');
        tmp->name = ft_strdup(tmp2[0]);
        tmp->value = ft_strdup(tmp2[1]);
        tmp->next = env;
        env = tmp;
        i++;
    }
    return (env);
}

static char **sort_env(char **envp)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strcmp(envp[i], envp[j]) < 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
            j++;
        }
        i++;
    }
    return (envp);
}

static char **list_to_str(t_env *env)
{
    char **envp;
    int i;
    t_env *tmp;
    char *tmp2;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    envp = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env)
    {
        tmp2 = ft_strjoin(env->name, "=");
        envp[i] = ft_strjoin(tmp2, env->value);
        free(tmp2);
        env = env->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}

void printEnv(t_data *data)
{
    t_env *tmp;

    tmp = data->env;
    while (tmp)
    {
        ft_putstr_fd("declare -x ", data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd(tmp->name, data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("=\"", data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd(tmp->value, data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("\"",data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("\n", data->exec->out_file); // is for test only to be replaced by exec->out_file
        tmp = tmp->next;
    }
}

void    export0(t_data *data)
{
    t_env *tmp;

    tmp = sort_environment(data);
       while (tmp)
    {
        ft_putstr_fd("declare -x ", data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd(tmp->name, data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("=\"", data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd(tmp->value, data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("\"",data->exec->out_file); // is for test only to be replaced by exec->out_file
        ft_putstr_fd("\n", data->exec->out_file); // is for test only to be replaced by exec->out_file
        tmp = tmp->next;
    }
}

t_env   *sort_environment(t_data *data)
{
    char **envp;
    t_env *tmp;

    envp = list_to_str(data->env);
    envp = sort_env(envp);
    tmp = strToList(envp);
    free(envp);
    return (tmp);
}