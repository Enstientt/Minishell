/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2022/12/25 12:46:32 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    t_data  data;

    data.buffer = NULL;
    while (1)
    {
        //// Reading the input line
        while (!data.buffer)
            data.buffer = readline("minishell$> ");
        /// Lexer : part one-> tokonizing the buffer
        lexer(&data);
        /// Lexer analyzer : generate errors / generate a valid linked list.
        free_data(&data);
    }
}
