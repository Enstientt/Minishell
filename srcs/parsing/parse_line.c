/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:04:41 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/20 13:37:45 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

////////////////////////////////// PARSE_LINE //////////////////////////////

void    parse_line(t_data *data)
{
    data->tokens = lexer(data);
    if (data->tokens)
    {
        data->tokens = syntax_analyzer(data);
        if (data->tokens && !data->err)
        {
            data->tokens = expander(data);
            if (data->tokens && !data->err)
            {
                // display_tokens(data->tokens);
                data->cmds = parser(data);
                if (!data->err)
                {
                    display_cmds(data->cmds);
                }
            }
        }
    }
}