/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:41:50 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/21 15:44:19 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(t_data *data, t_exec *cmd)
{
	if (!cmd)
		return (1);
	
	char *command = ft_tolower(cmd->str[0]);
	
	if (!ft_strcmp(command, "echo"))
		return (ft_echo(cmd), 0);
	
	if (!ft_strcmp(command, "cd"))
		return (ft_cd(data), 0);
	
	if (!ft_strcmp(command, "pwd"))
		return (ft_pwd(data), 0);
	
	if (!ft_strcmp(command, "export"))
		rerturn (ft_export(data, cmd), 0);
	
	if (!ft_strcmp(command, "unset"))
		//unset command
	
	if (!ft_strcmp(command, "env"))
	{
		if (cmd->str[1])
			return (ft_putstr_fd("env with No arguments\n", 2), 0);
		
		return (print_env(data->env, data), 0);
	}
	
	if (!ft_strcmp(command, "exit"))
		return (ft_exit(cmd), 0);
	
	return (1);
}
