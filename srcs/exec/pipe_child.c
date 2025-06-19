/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:49 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 00:21:20 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_child_redirections_and_exit(t_command *cmd, int *pipes,
		int index, int n_pipes)
{
	setup_pipe_redirections(pipes, index, n_pipes);
	if (!exec_redirections(cmd))
	{
		if (index == n_pipes)
		{
			if (!cmd->args || !cmd->args[0])
				exit(0);
			exit(1);
		}
		exit(0);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
}

void	execute_child_builtin_or_cmd(t_command *cmd, t_shell *shell)
{
	char	*path;

	if (is_builtin(cmd->args[0]))
	{
		g_exitcode = execute_builtin(cmd, shell);
		exit(g_exitcode);
	}
	path = get_exec_path(cmd->args[0], shell->env);
	if (!path)
	{
		g_exitcode = 127;
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("matteoshell: execve");
	free(path);
	exit(EXIT_FAILURE);
}

void	execute_child_pipe(t_command *cmd, int *pipes, int index,
		t_shell *shell)
{
	int	n_pipes;

	n_pipes = count_pipes(cmd);
	handle_child_redirections_and_exit(cmd, pipes, index, n_pipes);
	execute_child_builtin_or_cmd(cmd, shell);
}
