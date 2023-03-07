/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:41:50 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/07 20:37:11 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(t_data *data, t_exec	*cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "echo"))
		return (ft_echo(cmd), 0);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "cd"))
		return (ft_cd(data), 0);
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "pwd"))
		//ft_pwd 
	if (!ft_strcmp(cmd->str[0], "export"))
		//export 
	if (!ft_strcmp(cmd->str[0], "unset"))
		//unset command
	if (!ft_strcmp(ft_tolower(cmd->str[0]), "env"))
	{
		if (cmd->str[1])
			return (ft_putstr_fd("env with No arguments\n", 2), 0);
		return (print_env(data->env, data), 0);
	}
	if (!ft_strcmp(cmd->str[0], "exit"))
	{
		return (ft_exit(cmd), 0);
	}
	return (1);
}