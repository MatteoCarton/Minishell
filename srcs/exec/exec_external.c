/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:21:35 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:08:50 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exec_child_process(char *path, t_command *cmd, t_shell *shell)
{
	execve(path, cmd->args, shell->env);
	perror("matteoshell");
	exit(127);
}

/*
** Les redirections ne sont PAS appliquées ici : elles appartiennent à l'enfant
** (cf. handle_external_child). Les jouer aussi dans le parent consommait le
** heredoc — dup2 puis close — si bien que l'enfant retrouvait un heredoc_fd
** déjà fermé et échouait sur « dup2: Bad file descriptor ». C'est aussi le
** stdin du shell lui-même qui se faisait détourner, sans jamais être restauré.
*/
int	setup_external_exec(t_command *cmd, t_shell *shell, char **path)
{
	*path = get_exec_path(cmd->args[0], shell->env);
	if (!*path)
		return (0);
	return (1);
}

static int	handle_external_child(char *path, t_command *cmd, t_shell *shell)
{
	setup_child_signals();
	if (!exec_redirections(cmd))
	{
		free(path);
		exit(1);
	}
	exec_child_process(path, cmd, shell);
	return (0);
}

static int	create_child_exec(char *path, t_command *cmd, t_shell *shell,
		int stdout_backup)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("matteoshell: fork");
		g_exitcode = 1;
		free(path);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
		return (1);
	}
	if (pid == 0)
	{
		close(stdout_backup);
		return (handle_external_child(path, cmd, shell));
	}
	return (pid);
}

int	exec_external_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	int		stdout_backup;
	int		status;
	pid_t	child_pid;

	if (prepare_command_execution(cmd, shell, &stdout_backup, &path))
		return (g_exitcode);
	child_pid = create_child_exec(path, cmd, shell, stdout_backup);
	if (child_pid <= 0)
		return (1);
	signal(SIGINT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	free(path);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	return (handle_wait_status(status));
}
