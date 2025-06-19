/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:46 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 01:29:58 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_child_status(pid_t pid, pid_t last_pid, int status,
		int *last_status)
{
	if (pid == last_pid)
	{
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*last_status = 128 + WTERMSIG(status);
	}
}

void	wait_all_children(int n_cmd, pid_t *pids)
{
	int		status;
	int		i;
	pid_t	current_pid;
	pid_t	last_pid;
	int		last_status;

	i = 0;
	last_status = 0;
	if (n_cmd > 0)
		last_pid = pids[n_cmd - 1];
	else
		last_pid = -1;
	while (i < n_cmd)
	{
		current_pid = wait(&status);
		handle_child_status(current_pid, last_pid, status, &last_status);
		i++;
	}
	g_exitcode = last_status;
	free(pids);
}

static void	parent_close_fds(int *pipes, int i, int n_pipes)
{
	if (i > 0)
		close(pipes[(i - 1) * 2]);
	if (i < n_pipes)
		close(pipes[i * 2 + 1]);
}

int	fork_children(t_command *cmd, int *pipes, t_shell *shell, pid_t *pids)
{
	int			i;
	t_command	*current;
	int			n_pipes;

	i = 0;
	current = cmd;
	n_pipes = count_pipes(cmd);
	while (current)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (perror("matteoshell: fork"), 1);
		if (pids[i] == 0)
			execute_child_pipe(cmd, pipes, i, shell);
		parent_close_fds(pipes, i, n_pipes);
		current = current->next;
		i++;
	}
	return (0);
}

int	exec_pipe(t_command *cmd, t_shell *shell)
{
	int		*pipes;
	int		n_pipes;
	int		n_cmd;
	int		i;
	pid_t	*pids;

	i = 0;
	if (init_pipe_data(cmd, &pipes, &n_pipes, &n_cmd) == 1)
		return (1);
	pids = malloc(sizeof(pid_t) * n_cmd);
	if (!pids)
		return (free(pipes), 1);
	if (fork_children(cmd, pipes, shell, pids))
		return (free(pipes), free(pids), 1);
	while (i < n_pipes * 2)
		close(pipes[i++]);
	wait_all_children(n_cmd, pids);
	free(pipes);
	return (g_exitcode);
}
