/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:31:46 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/22 14:59:07 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

///----------------- close the file [Doc] when finish using it ---------------------/

char    *filename_gener(char *filename, int index_file)
{
    char    *new_file;

    new_file = ft_strjoin(filename, ft_itoa(index_file));
    free(filename);
    return (new_file);
}

void    open_doc(t_data *data)
{
    char    *filename;
    int     index_file;

    index_file = 0;
    filename = ft_strdup("tmp");
    data->cmds->in_file = open (filename, O_RDONLY);
    while (data->cmds->in_file != -1)
    {
        close(data->cmds->in_file);
        index_file++;
        filename = filename_gener(filename, index_file);
        data->cmds->in_file = open(filename, O_RDONLY);
    }
    close(data->cmds->in_file);
    data->cmds->in_file = open(filename, O_RDWR | O_APPEND | O_CREAT, 0644);
    free(filename);
}

int heredoc_handler(t_data *data)
{
    char    *line;

    line = ft_strdup("");
    open_doc(data);
    while (1)
    {
        free(line);
        line = readline("heredoc> ");
        if (ft_strcmp(data->tokens->next->lex, line) == 0)
            break;
        if (line && line[0] != '\n' && line[0] != '\0' && white_check(line))
        {
            ft_putstr_fd(line, data->cmds->in_file);
            ft_putchar_fd('\n', data->cmds->in_file);
        }
    }
    data->tokens = data->tokens->next->next;
    return (1);
}