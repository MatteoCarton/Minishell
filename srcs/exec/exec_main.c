/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:21:46 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 11:14:12 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_is_directory(const char *path)
{
	struct stat	st;

	stat(path, &st);
	if (S_ISDIR(st.st_mode))
	{
		print_file_error(path, ": Is a directory\n");
		g_exitcode = 126;
		return (0);
	}
	return (1);
}

int	prepare_command_execution(t_command *cmd, t_shell *shell,
		int *stdout_backup, char **path)
{
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdout_backup == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!setup_external_exec(cmd, shell, path))
	{
		dup2(*stdout_backup, STDOUT_FILENO);
		close(*stdout_backup);
		return (g_exitcode);
	}
	return (0);
}

int	handle_builtin_no_redir(t_command *cmd, t_shell *shell, int stdout_backup)
{
	int	ret;

	stdout_backup = dup(STDOUT_FILENO);
	if (stdout_backup == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!exec_redirections(cmd))
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
		g_exitcode = 1;
		return (1);
	}
	ret = execute_builtin(cmd, shell);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	return (ret);
}

int	handle_simple_command(t_command *cmd, t_shell *shell)
{
	int	has_output_redirection;
	int	stdout_backup;

	stdout_backup = -1;
	has_output_redirection = check_output_redirection(cmd);
	if (is_builtin(cmd->args[0]) && !has_output_redirection)
		return (handle_builtin_no_redir(cmd, shell, stdout_backup));
	if (is_builtin(cmd->args[0]))
		return (exec_builtin_with_fork(cmd, shell));
	return (exec_external_command(cmd, shell));
}

int	exec(t_command *cmd, t_shell *shell)
{
	if (!cmd)
		return (0);
	init_heredoc_fds(cmd);
	if (cmd && cmd->next)
		return (exec_pipe(cmd, shell));
	if (!cmd->args || !cmd->args[0])
		return (0);
	return (handle_simple_command(cmd, shell));
}
