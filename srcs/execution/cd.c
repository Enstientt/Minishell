/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/02/26 00:12:38 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cd_only(t_cmd	*tmp, t_data	*data)
{
	char	*str;
	char	*tmp1;

	if (!tmp->next)
	{
		str = get_ev(data, "HOME");
		tmp1 = getcwd(NULL, PATH_MAX);
		//export here with the old pwd
		if (chdir(str) == -1)
		{
			exitS = 1;
			perror(str);
		}
		else
			//export here also with pwd
		free(tmp1);
		exitS = 0;
		return (0);
	}
	return (1);
}

void	ft_cd(t_data	*data)
{
	t_cmd	*tmp;
	char	*str;

	tmp = data->cmd;
	if (!cd_only(tmp, data))
		return ;
	else
	{
		if (tmp->next)
			tmp = tmp->next;
		str = getcwd(NULL, PATH_MAX);
		//export OLDPWD
		if (chdir(tmp->next->str) == -1)
			return (perror("cd "), exitS = 1, (void)0);
		else
			//export "PWD"
		free(str);
		exitS = 0;
	}
}