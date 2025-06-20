/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:49 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:13:47 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_child_redirections_and_exit(t_command *cmd, int *pipes,
		int index, int n_pipes)
{
	setup_pipe_redirections(pipes, index, n_pipes);
	if (!exec_redirections(cmd))
	{
		if (index >= n_pipes)
			exit(1);
		exit(0);
	}
	if (!cmd->args || !cmd->args[0])
		exit(0);
}

static void	execute_child_builtin_or_cmd(t_command *cmd, t_shell *shell)
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

void	execute_child_pipe(t_command *cmd_head, int *pipes, int index,
		t_shell *shell)
{
	t_command	*current;
	int			n_pipes;
	int			i;

	current = cmd_head;
	i = 0;
	while (i < index)
	{
		current = current->next;
		i++;
	}
	n_pipes = count_pipes(cmd_head);
	handle_child_redirections_and_exit(current, pipes, index, n_pipes);
	execute_child_builtin_or_cmd(current, shell);
}

void	parent_cleanup(int *pipes, int n_pipes, int n_cmd, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < n_pipes * 2)
		close(pipes[i++]);
	wait_all_children(n_cmd, pids);
	setup_shell_signals();
	free(pipes);
}

void	parent_close_fds(int *pipes, int i, int n_pipes)
{
	if (i > 0)
		close(pipes[(i - 1) * 2]);
	if (i < n_pipes)
		close(pipes[i * 2 + 1]);
}
