/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 15:20:01 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    t_data  data;
    int     buffer_size;

    data.buffer = NULL;
    buffer_size = 0;
    while (1)
    {
        //// Reading the input line
        while (buffer_size == 0)
        {
            data.buffer = readline("minishell$> ");
            buffer_size = ft_strlen(data.buffer);
        }
        /// Lexer : part one-> tokonizing the buffer
        lexer(&data);
        /// Lexer analyzer : generate errors / generate a valid linked list.
        
        free_data(&data);
        buffer_size = 0;
    }
}
