/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:06:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/07 20:45:24 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipes_redirection(t_exec *tmp, int file_, int i, t_data *data)
{
	int			status;

	if (rederection_check(&tmp, file_))
	{
		if (tmp->in_file == -1)
			return (-1);
		red_inp(tmp, status, data, i);
		if (tmp->out_file != 1)
		{
			if (i != data->pipex->p_c)
				dup2(tmp->out_file, data->pipex->p_fd[i][1]);
			else
				dup2(tmp->out_file, 1);
		}
	}
	return (0);
}

void	handle_fds(t_data *data, int i)
{
	int	j;

	j = -1;
	while (++j < data->pipex->p_c)
	{
		if (j + 1 != i || i == 0)
			close(data->pipex->p_fd[j][0]);
		if (i == data->pipex->p_c || i != j)
			close(data->pipex->p_fd[j][1]);
	}
	if (i != 0)
	{
		dup2(data->pipex->p_fd[i - 1][0], 0);
		close(data->pipex->p_fd[i - 1][0]);
	}
	if (i != data->pipex->p_c)
	{
		dup2(data->pipex->p_fd[i][1], 1);
		close(data->pipex->p_fd[i][1]);
	}
}

void	restore_parent(int	*stds, int status, int	*pids, t_data	*data)
{
	int		i;

	dup2(stds[0], 0);
	dup2(stds[1], 1);
	if (status == 1)
	{
		i = -1;
		close_fds(data);
		while (++i <= data->pipex->p_c)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				exitS = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					ft_putstr_fd("\n", 1);
					exitS = 130;
				}
			}
		}
		signals_handler();
	}
}

void	pipe_exe(int *pids, t_data	*data, t_exec *tmp, int i)
{
	int	status;

	if (pids[i] == 0)
	{
		handle_fds(data, i);
		if (!builtin(data, tmp))
			;
		else
		{
			if (execve(get_path(tmp->str, data, &status),
					tmp->str, data->envp_) == -1)
			{
				exitS = 127;
				perror("Minishell ");
			}
		}
		exit(exitS);
	}
}

void	exec_pipes(t_exec *exc, t_data *data, int file_, char **envp_)
{
	t_vars	pipe;

	pipe.i = 0;
	pipe.status = 1;
	pipe.tmp = exc;
	pipe.pids = malloc(sizeof(int) * (data->pipex->p_c + 1));
	pipe.std = save_stds();
	if (data->pipex->p_c)
		data->pipex->p_fd = create_pipes(data->pipex->p_c);
	while (pipe.i <= data->pipex->p_c && pipe.tmp)
	{
		handle_loop(pipe, file_, data);
		pipe.tmp = pipe.tmp->next;
		pipe.i++;
	}
	restore_parent(pipe.std, 1, pipe.pids, data);
	free(pipe.std);
	free(pipe.pids);
	//free the pids
}
