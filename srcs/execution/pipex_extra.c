/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 20:17:53 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/07 20:45:09 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pps(t_exec	*exec)
{
	int		cnt;
	t_exec	*tmp;

	cnt = 0;
	tmp = exec;
	while (tmp)
	{
		if (tmp->next)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

int	**pipe_gener(int count)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		return (0);
	while (++i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
	}
	return (pipes);
}

void	red_inp(t_exec	*tmp, int status, t_data	*data, int i)
{
	if (tmp->in_file != 0)
	{
		if (i != 0)
			dup2(tmp->in_file, data->pipex->p_fd[i - 1][0]);
		else
			dup2(tmp->in_file, 0);
	}
	return ;
}

int	*save_std(void)
{
	int	*stds;

	stds = malloc(sizeof(int) * 2);
	stds[0] = dup(0);
	stds[1] = dup(1);
	return (stds);
}

void	close_fd(t_data	*data)
{
	int	i;

	i = -1;
	while (++i < data->pipex->p_c)
	{
		close(data->pipex->p_fd[i][0]);
		close(data->pipex->p_fd[i][1]);
	}
}

void	handle_loop(t_vars	pipe, int her_file, t_data	*data)
{
	restore_parent(pipe.std, 0, pipe.pids, data);
	//herdoc handler
	pipe.status = pipes_redirection(pipe.tmp, her_file, pipe.i, data);
	if (pipe.status == -1)
		return ;
	pipe.pids[pipe.i] = fork();
	if (pipe.pids[pipe.i] == -1)
	{
		perror("fork");
		restore_parent(pipe.std, 1, pipe.pids, data);
		exitS = 1;
		return ;
	}
	if (pipe.pids[pipe.i])
		ignore_signal();
	pipe_exe(pipe.pids, data, pipe.tmp, pipe.i);
}