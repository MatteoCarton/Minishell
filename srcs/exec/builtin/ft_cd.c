/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:50:32 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 16:29:05 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	change_directory(char *arg1, t_shell *shell)
{
	if (chdir(arg1) == -1)
	{
		perror("matteoshell: cd");
		g_exitcode = 1;
		return ;
	}
	if (update_new_pwd_env(shell->env) == 1)
	{
		g_exitcode = 1;
		return ;
	}
	g_exitcode = 0;
}

void	ft_cd(char **args, t_shell *shell)
{
	char	*home_path;

	if (number_of_args(args) > 2)
	{
		write(2, "matteoshell: cd: too many arguments\n", 36);
		g_exitcode = 1;
		return ;
	}
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			write(2, "matteoshell: cd: HOME not set\n", 30);
			g_exitcode = 1;
			return ;
		}
		change_directory(home_path, shell);
	}
	else
		change_directory(args[1], shell);
}
