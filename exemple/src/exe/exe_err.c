/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:10:00 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 16:09:29 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fd_err(char **str)
{
	write(2, *str, ft_strlen(*str));
	write(2, ": ", 2);
	perror(NULL);
	g_excode = 1;
	free(*str);
	*str = NULL;
}

void	fork_err_dir(char **str)
{
	perror("fork failed");
	g_excode = 1;
	free(*str);
	*str = NULL;
}

void	ft_execv_error(char **split_cmd)
{
	write(2, "mini-flemme: ", 13);
	ft_print(split_cmd[0]);
	if (split_cmd[0][0] == '/' || (split_cmd[0][0] == '.'
		&& split_cmd[0][1] == '/'))
	{
		ft_free_str(split_cmd);
		write(2, ": No such file or directory\n", 28);
		exit(126);
	}
	else
	{
		ft_free_str(split_cmd);
		write(2, ": command not found\n", 20);
		exit(127);
	}
}
