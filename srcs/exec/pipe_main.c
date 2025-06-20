/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:46 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 02:00:55 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	wait_last_child(int n_cmd, pid_t *pids, int *last_status)
{
	int	status;
	int	was_signaled;

	was_signaled = 0;
	*last_status = 0;
	if (n_cmd > 0)
	{
		waitpid(pids[n_cmd - 1], &status, 0);
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			was_signaled = 1;
			*last_status = 128 + WTERMSIG(status);
		}
	}
	return (was_signaled);
}

void	wait_all_children(int n_cmd, pid_t *pids)
{
	int	last_status;
	int	signaled_last;
	int	signaled_remaining;

	signaled_last = wait_last_child(n_cmd, pids, &last_status);
	signaled_remaining = wait_remaining_children(n_cmd);
	if (signaled_last || signaled_remaining)
		write(1, "\n", 1);
	g_exitcode = last_status;
	free(pids);
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
	pid_t	*pids;

	if (init_pipe_data(cmd, &pipes, &n_pipes, &n_cmd))
		return (1);
	pids = malloc(sizeof(pid_t) * n_cmd);
	if (!pids)
		return (free(pipes), 1);
	signal(SIGINT, SIG_IGN);
	if (fork_children(cmd, pipes, shell, pids))
	{
		setup_shell_signals();
		free(pipes);
		free(pids);
		return (1);
	}
	parent_cleanup(pipes, n_pipes, n_cmd, pids);
	return (g_exitcode);
}
