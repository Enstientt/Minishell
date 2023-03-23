/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zessadqu <zessadqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:15:39 by zessadqu          #+#    #+#             */
/*   Updated: 2023/03/10 19:04:58 by zessadqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_to_home_directory(char *home_dir, char *oldpwd_var)
{
    char *cwd = getcwd(NULL, PATH_MAX);
    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }

    if (do_export("OLDPWD", cwd, false) == -1)
    {
        free(cwd);
        return 1;
    }

    if (chdir(home_dir) == -1)
    {
        perror(home_dir);
        free(cwd);
        return 1;
    }

    free(cwd);

    if (do_export("PWD", home_dir, false) == -1)
        return 1;

    return 0;
}

static int	change_to_directory(char *dir_path)
{
    char *cwd = getcwd(NULL, PATH_MAX);
    if (cwd == NULL)
    {
        perror("getcwd");
        return 1;
    }

    if (do_export("OLDPWD", cwd, false) == -1)
    {
        free(cwd);
        return 1;
    }

    if (chdir(dir_path) == -1)
    {
        perror(dir_path);
        free(cwd);
        return 1;
    }

    free(cwd);

    if (do_export("PWD", dir_path, false) == -1)
        return 1;

    return 0;
}

void	ft_cd(void)
{
    char *home_dir = env_("HOME");

    if (get_next_arg() == NULL)
    {
        if (change_to_home_directory(home_dir, "OLDPWD") == 0)
            exitS = 0;
    }
    else
    {
        char *dir_path = get_next_arg();
        if (change_to_directory(dir_path) == 0)
            exitS = 0;
    }
}
