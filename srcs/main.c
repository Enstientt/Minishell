/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/03/18 18:58:41 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     buffer_size;
    t_exec  exec;

    // data.envp_= envp;
    // exec.str = malloc(sizeof(char**) * 3);
    // exec.str[0] = ft_strdup("cd");
    // exec.str[1] = ft_strdup("/Users/zessadqu/Desktop/test");
    // exec.str[2] = NULL;
    // exec.in_file = 0;
    // exec.out_file = 1;
    // data.exec = &exec;
    if (ac == 1)
    {
        data.buffer = ft_strdup("");
        data.envp_ = ft_2strdup(envp);
        while (1)
        {
            //signals_handler();
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
            execute_command(&data.exec, get_path(&data.exec->str[0],&data, &buffer_size), envp);
        //     ft_cd(&data);
        //    ft_pwd(&data);
             //ft_pwd(&data);
            //printf("we are in main.c and data.buffer is:");
            /////// EXECUTION PART /////
            //free_data(&data);
        }
    }
    return(0);
}
