/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 22:04:41 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:21:05 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

////////////////////////////////// PARSE_LINE //////////////////////////////

t_tokens    *parse_line(t_data *data)
{
    t_tokens    *head;

    head = data->tokens;
    data->tokens = lexer(data);
    if (data->tokens)
    {
        data->tokens = syntax_analyzer(data);
        if (data->tokens && data->err == 0)
        {
            data->tokens = expander(data);
            if (data->tokens && data->err == 0)
            {
                // printf("Error status: [ %d ]\n", data->err);
                display_list(data->tokens);
            }
        }
    }
    return (head);
}