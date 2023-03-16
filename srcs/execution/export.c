/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:24:41 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/16 20:40:06 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int     check_append(char *str)
{
        int     i;

        i = 0;
        while (str[i] && str[i] != '=')
                i++;
        if (str[i] == '=' && str[i - 1] == '+')
                return (1);
        return (0);
}
{
                
}
static char    *extract_name(char *str, bool *append)
{
        int     i;
        char    *name;

        i = 0;
        while (str[i] && str[i] != '=')
                i++;
        if (str[i] == '=' && check_append(str))
                *append = true;
        if(append)
        {
                name = ft_substr(str, 0, i - 1);
        }
        else
        {
                name = ft_substr(str, 0, i);
        }
        if(special_param(name))
        {
		ft_putstr_fd("special param not supported\n", 2);
                return (NULL);
        }
        return (name);
        
}

static char    *extract_value(char *str, bool append)
{
        int     i;

        i = 0;
        while (str[i] && str[i] != '=')
                i++;
        if (str[i] == '=')
                return (ft_substr(str, i + 1, ft_strlen(str) - i));
        return (NULL);
}
int special_param(const char* str)
{
        int i = 0;
        if (!ft_isalpha(str[i]) && str[i] != '_')
                return 1;
                while (str[++i])
                {
                        if (!ft_isalnum(str[i]) && str[i] != '_')
                                return 1;
                }
                return 0;
}

static t_env *find_env_node(t_env *env, const char *name)
{
        while (env)
        {
                if (!ft_strcmp(env->name, name))
                        return env;
        env = env->next;
        }
        return NULL;
}

void appendEnv(t_data *data, const char *name, const char *val)
{
        char    *new_val;
        size_t  new_val_len ;
        t_env   *node;
        t_env   *new_node;

        node = find_env_node(data->env, name);
    if (node)
    {
        if (node->value)
        {
            new_val_len = strlen(node->value) + strlen(val);
            new_val = malloc(new_val_len + 1);
            ft_strlcpy(new_val, node->value, new_val_len + 1);
            ft_strlcat(new_val, val, new_val_len + 1);
            free(node->value);
            node->value = new_val;
        }
        else
                node->value = ft_strdup(val);
    }
    else
    {
        new_node = newEnvNode(ft_strdup(name), ft_strdup(val));
        addBackEnvNode(&data->env, new_node);
    }
}

t_env *newEnvNode(char *name, char *value)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node) {
        return NULL;
    }
    node->name = name;
    node->value = value;
    node->next = NULL;
    return node;
}

void addBackEnvNode(t_env **env, t_env *new_node)
{
        t_env *current;
        
        if (!env || !new_node)
                return;
        if (!*env)
        {
                *env = new_node;
                return ;
        }
        current = *env;
        while (current->next)
                current = current->next;
    current->next = new_node;
}



void export1(t_data *data, char *name, char *value, bool append)
{
        t_env *node;

        if (append)
        {
                appendEnv(data, name, value);
                return;
        }
	node = find_env_node(data->env, name);
        if (node)
        {
                if (value)
                {
                        free(node->value);
                        node->value = ft_strdup(value);
                }
        }
        else
        {
                if (value)
                        addBackEnvNode(&data->env, newEnvNode(ft_strdup(name), ft_strdup(value)));
                else
                        addBackEnvNode(&data->env, newEnvNode(ft_strdup(name), NULL));
        }
}

void    ft_export(t_data *data, t_exec *cmd)
{
        char    *name;
        char    *value;
        int     i;
        bool    append;
        
        i = 1;
        if(cmd->str[1] == NULL)
        {
                print_env(data->env);  //print_env is a function that prints the env list in the format NAME=VALUE
                return;
        }
        while (cmd->str[i])
        {
                append = false;
                name = extract_name(cmd->str[i], &append);
                if (!name)
                        return;
                value = extract_value(cmd->str[i], append);
                export1(data, name, value, append);
                free(name);
                free(value);
                i++;
        }       
}