/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:41:50 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/26 23:03:22 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_tolower1(char *str)
{
	int i;
	char *tmp;
	
	i = 0;
	tmp = ft_strdup(str);
	while (tmp[i])
	{
		tmp[i] = ft_tolower(tmp[i]);
		i++;
	}
	return (tmp);
}
int	builtin(t_data *data, t_exec *cmd)
{
	char *command = ft_tolower1(cmd->str[0]);
	if (!cmd)
		return (1);
	
	
	if (!ft_strcmp(command, "echo"))
		return (ft_echo(cmd), 0);
	
	if (!ft_strcmp(command, "cd"))
		return (ft_cd(data), 0);
	
	if (!ft_strcmp(command, "pwd"))
		return (ft_pwd(data), 0);
	
	if (!ft_strcmp(command, "export"))
		return (ft_export(data, cmd), 0);
	
	if (!ft_strcmp(command, "unset"))
		return (ft_unset(cmd, data), 0);
	
	if (!ft_strcmp(command, "env"))
	{
		if (cmd->str[1])
			return (ft_putstr_fd("env with No arguments\n", 2), 0);
		
		return (printEnv(data), 0);
	}
	
	if (!ft_strcmp(command, "exit"))
		return (ft_exit(cmd), 0);
	
	return (1);
}
