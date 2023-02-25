/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:55:15 by zessadqu          #+#    #+#             */
/*   Updated: 2023/02/25 02:00:27 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	words(t_exec	*exec, int i)
{
	char	**rest;
	int		j;

	if (exec->flg[i] == '1')
	{
		j = 0;
		rest = ft_split(exec->str[i], ' ');
		while (rest[j])
		{
			ft_putstr_fd(rest[j], exec->out_file);
			if (rest[j + 1])
				ft_putstr_fd(" ", exec->out_file);
			j++;
		}
		free_tab(rest);
	}
	else
		ft_putstr_fd(exec->str[i], exec->out_file);
}

static	int	check_opt(t_exec	*exec, bool	*mode)
{
	int		i;
	int		j;
	t_exec	*tmp;

	i = 0;
	j = 0;
	tmp = exec;
	*mode = false;
	while (exec->str[++i])
	{
		j = 0;
		if (exec->str[i][j++] == '-' && exec->str[i][1] == 'n')
		{
			while (exec->str[i][j] == 'n')
				j++;
			if (!exec->str[i][j])
				*mode = true;
			else
				return (i);
		}
		else
			break ;
	}
	return (i);
}

void	ft_echo(t_exec	*exec)
{
	int		i;
	bool	mode;

	i = check_opt(exec, &mode);
	if (!exec->str[1])
	{
		if (!mode)
			return (ft_putstr_fd("\n", exec->out_file), (void)0);
		else
			return ;
	}
	while (exec->str[i])
	{
		words(exec, i);
		if (exec->str[i + 1])
			ft_putstr_fd(" ", exec->out_file);
		i++;
	}
	if (!mode)
		ft_putstr_fd("\n", exec->out_file);
	exitS = 0;
}