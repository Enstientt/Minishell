/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:13:54 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/27 01:14:54 by ahammout         ###   ########.fr       */
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