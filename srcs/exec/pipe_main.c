/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:46 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 00:31:17 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_all_children(int n_cmd)
{
	int		status;
	int		i;
	pid_t	current_pid;
	int		last_status;

	i = 0;
	last_status = 0;
	while (i < n_cmd)
	{
		current_pid = wait(&status);
		if (current_pid > 0)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGPIPE)
					last_status = 0;
				else
					last_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	g_exitcode = last_status;
}

int	init_pipe_data(t_command *cmd, int **pipes, int *n_pipes, int *n_cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	*n_pipes = count_pipes(cmd);
	*n_cmd = *n_pipes + 1;
	if (alloc_pipe_array(pipes, *n_pipes))
		return (1);
	if (create_pipes(*pipes, *n_pipes))
	{
		free(*pipes);
		return (1);
	}
	return (0);
}

static int	handle_fork_process(t_command *current, int *pipes, int i,
		t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("matteoshell: fork");
		g_exitcode = 1;
		free(pipes);
		return (1);
	}
	if (pid == 0)
		execute_child_pipe(current, pipes, i, shell);
	return (0);
}

int	fork_children(t_command *cmd, int *pipes, t_shell *shell)
{
	int			i;
	t_command	*current;
	int			n_pipes;

	i = 0;
	current = cmd;
	n_pipes = count_pipes(cmd);
	while (current)
	{
		if (handle_fork_process(current, pipes, i, shell))
			return (1);
		if (i > 0)
			close(pipes[(i - 1) * 2]);
		if (i < n_pipes)
			close(pipes[i * 2 + 1]);
		current = current->next;
		i++;
	}
	return (0);
}

int	exec_pipe(t_command *cmd, t_shell *shell)
{
	int	*pipes;
	int	n_pipes;
	int	n_cmd;
	int	i;

	i = 0;
	if (init_pipe_data(cmd, &pipes, &n_pipes, &n_cmd) == 1)
		return (1);
	signal(SIGINT, SIG_IGN);
	if (fork_children(cmd, pipes, shell) == 1)
		return (1);
	while (i < n_pipes * 2)
		close(pipes[i++]);
	wait_all_children(n_cmd);
	free(pipes);
	return (g_exitcode);
}
