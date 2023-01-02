/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <ahammout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:14:07 by ahammout          #+#    #+#             */
/*   Updated: 2023/01/02 17:17:51 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

        ////// CHECK THE SYNTAX : GENERATE ERRORS / GENERATE VALID COMMAND ///////
        /* 
            RETURN : SECCUES : + VALID SYNTAX ==> LINKED LIST[TOKENAZED].
                    FAILURE : + INVALID SYNTAX ==> ERROR MESSAGE & RETURN NULL.
        */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    t_data  data;
    int     buffer_size;

    if (ac == 1)
    {
        data.buffer = ft_strdup("");
        data.envp_ = ft_2strdup(envp);
        av = NULL;
        while (1)
        {
            buffer_size = 0;
            data.err = 0;
            while (buffer_size == 0)
            {
                free(data.buffer);
                data.buffer = readline("minishell $> ");
                buffer_size = ft_strlen(data.buffer);
            }
            data.token = lexer(&data);
            if (data.token)
            {
                data.token = syntax_checker (&data);
                exit(0);
                if (data.token && data.err == 0)
                {
                    printf("non Error\n");
                    display_list(data.token);
                }
            }
            free_data(&data);
        }
    }
    // expander(&data, "$PWD from the env", NULL);
    return(0);
}
