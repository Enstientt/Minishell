/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:13:06 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/20 13:34:03 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int update_size(char *lexem, char *pids, char *value)
{
    int len;
    int i;

    len = 0;
    i = 0;
    if (lexem && (ft_isdigit(lexem[i]) || lexem[i] == '@' || lexem[i] == '*'))
    {
        i++;
        while (lexem[i])
        {
            len++;
            i++;
        }
    }
    if (value)
        return ((ft_strlen(pids) - 1) + ft_strlen(value));
    return (len + (ft_strlen(pids) - 1));
}

void var_not_exist(t_data *data, char *lexem, char *pids)
{
    t_reference ref;
    int size;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    size = update_size(lexem, pids, NULL);
    if (!size)
    {
        data->tokens->lex = NULL;
        data->tokens->type = EMPTY;
    }
    else
    {
        data->tokens->lex = ft_calloc(size, sizeof(char));
        while (pids[ref.j + 1])
            data->tokens->lex[ref.l++] = pids[ref.j++];
        if (lexem[ref.i] == '@' || lexem[ref.i] == '*' || ft_isdigit(lexem[ref.i]))
        {
            ref.i++;
            while (lexem[ref.i])
                data->tokens->lex[ref.l++] = lexem[ref.i++];
            data->tokens->lex[ref.l] = '\0';
        }
    }
}

void var_exist(t_data *data, char *pids, char *value)
{
    t_reference ref;

    ref.i = 0;
    ref.j = 0;
    ref.l = 0;
    data->tokens->lex = ft_calloc((update_size(NULL, pids, value)), sizeof(char));
    while (pids[ref.j + 1])
        data->tokens->lex[ref.l++] = pids[ref.j++];
    while (value[ref.i])
        data->tokens->lex[ref.l++] = value[ref.i++];
    data->tokens->lex[ref.l] = '\0';
}

char *get_value(t_data *data, char *var)
{
    t_env   *head;
    char    *value;

    value = NULL;
    head = data->env;
    if (!var)
        return (0);
    while (data->env)
    {
        if (ft_strcmp(var, data->env->name) == 0)
        {
            value = ft_strdup(data->env->value);
            break;
        }
        data->env = data->env->next;
    }
    data->env = head;
    return (value);
}

char *get_var(t_data *data, char *lexem)
{
    int i;
    int len;
    char *var;

    len = 0;
    i = 0;
    while (lexem[len] && (ft_isalpha(lexem[len]) || ft_isdigit(lexem[len]) || lexem[len] == '_' || lexem[len] == '@' || lexem[len] == '*'))
        len++;
    var = malloc(sizeof(char) * len);
    if (!var)
        exit_error(data, "Minishell: Allocation failed.");
    while (lexem[i] && (ft_isalpha(lexem[i]) || ft_isdigit(lexem[i]) || lexem[i] == '_' || lexem[i] == '@' || lexem[len] == '*'))
    {
        var[i] = lexem[i];
        i++;
    }
    var[i] = '\0';
    return (var);
}

void expandable(t_data *data, char *lexem, char *pids)
{
    char *var;
    char *value;
    int i;

    i = 0;
    while (lexem[i] == EXPAND_)
        i++;
    var = get_var(data, lexem + i);
    value = get_value(data, var);
    if (value)
        var_exist(data, pids, value);
    else
        var_not_exist(data, lexem + i, pids);
    free(var);
    free(value);
}