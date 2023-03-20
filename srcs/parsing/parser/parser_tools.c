/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:59:47 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/19 12:28:41 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    free_cmds_list(t_data *data)
{
    t_exec  *to_free;
    int     i;

    while (data->cmds != NULL)
    {
        to_free = data->cmds;
        i = 0;
        while (data->cmds->str[i])
        {
            free(data->cmds->str[i]);
            i++;
        }
        data->cmds = data->cmds->next;
        free(to_free);
    }
}

void    next_cmd(t_data *data)
{
    t_exec  *node;

    node = malloc(sizeof (t_exec));
    if (!node)
    {
        free_cmds_list(data);
        exit_error (data, "Minishell: Allocation failed");
    }
    node->in_file = 0;
    node->out_file = 1;
    node->next = NULL;
    data->cmds->next = node;
    data->cmds = data->cmds->next;
}

void    init_cmds_list(t_data *data)
{
    data->cmds = malloc(sizeof(t_exec));
    if (!data->cmds)
    {
        free_cmds_list(data);
        exit_error(data, "Minishell: Allocation failed");
    }
    data->cmds->in_file = 0;
    data->cmds->out_file = 1;
    data->cmds->next = NULL;
}

int is_redirection(int type)
{
    if (type == REDIN || type == REDOUT \
        || type == APPEND || type == HEREDOC)
        return (1);
    return (0);
}

void    display_cmds(t_exec *cmds)
{
    t_exec *head;
    int     n;
    int     i;

    head = cmds;
    n = 0;
    while (cmds != NULL)
    {
        i = 0;
        printf ("-------------- CMD %d -----------------\n\n", n++);
        while (cmds->str[i])
        {
            printf("  + Str [ %d ]: %s\n", i, cmds->str[i]);
            i++;
        }
        printf("\n");
        printf("* Input FD: %d\n", cmds->in_file);
        printf("* Output FD: %d\n\n", cmds->out_file);
        if (cmds->in_file != 0)
        {
            printf("In_file ==> File Content: %s\n", get_next_line(cmds->in_file));
        }
        if (cmds->out_file != 1)
        {
            ft_putstr_fd(cmds->str[1], cmds->out_file);
            printf("Out_file ==> File Content : %s\n", get_next_line(cmds->out_file));
        }
        cmds = cmds->next;
    }
    cmds = head;
}