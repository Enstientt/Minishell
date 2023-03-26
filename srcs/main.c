/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/26 01:40:38 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     buffer_size;

    (void)**av;
    if (ac == 1)
    {
        data.envp_ = envp;
        data.buffer = NULL;
        set_environment(&data, envp);
        // minishell_sig_handler(&data);
        while (1)
        {
            buffer_size = 0;
            data.err = 0;
            while (!buffer_size)
            {
                data.buffer = readline("minishell$> ");
                buffer_size = ft_strlen(data.buffer);
            }
            add_history(data.buffer);
            parse_line(&data);
            /////// EXECUTION PART /////

        }
    }
    return (0);
}
