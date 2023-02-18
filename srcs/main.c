/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/02/18 14:21:10 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     buffer_size;

    (void) **av;
    if (ac == 1)
    {
        data.buffer = ft_strdup("");
        data.envp_ = ft_2strdup(envp);
        while (1)
        {
            buffer_size = 0;
            data.err = 0;
            while (!buffer_size)
            {
                free(data.buffer);
                data.buffer = readline("minishell$> ");
                buffer_size = ft_strlen(data.buffer);
            }
            add_history (data.buffer);
            parse_line(&data);
            /////// EXECUTION PART /////
            free_data(&data);
        }
    }
    return(0);
}
