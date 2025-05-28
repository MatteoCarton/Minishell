/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:07 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 15:29:18 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	ft_change_directory(char *path)
{
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		g_excode = 1;
	}
	else
		g_excode = 0;
}

void	ft_cd(char **args)
{
	char	*home;
	char	*error_msg;

	if (args[2])
	{
		g_excode = 1;
		write(2, " too many arguments\n", 19);
		return ;
	}
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			error_msg = "minishell: cd: HOME not set\n";
			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
			g_excode = 0;
			return ;
		}
		ft_change_directory(home);
	}
	else
		ft_change_directory(args[1]);
}
