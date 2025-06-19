/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:21:32 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 10:22:13 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strncmp(arg, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(arg, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(arg, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(arg, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(arg, "env", 4) == 0)
		return (1);
	if (ft_strncmp(arg, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(arg, "export", 7) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		return (ft_exit(cmd->args));
	}
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (ft_echo(cmd->args));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (ft_pwd(), g_exitcode);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (ft_cd(cmd->args, shell), g_exitcode);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (ft_env(shell->env), g_exitcode);
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (unset_env(cmd->args, &shell->env, cmd->args[1], &g_exitcode),
			g_exitcode);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (export_env(cmd->args, &shell->env, &g_exitcode), g_exitcode);
	return (0);
}

int	create_builtin_process(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		g_exitcode = 1;
		return (-1);
	}
	if (pid == 0)
	{
		g_exitcode = execute_builtin(cmd, shell);
		exit(g_exitcode);
	}
	return (pid);
}

int	exec_builtin_with_fork(t_command *cmd, t_shell *shell)
{
	int		stdout_backup;
	pid_t	pid;
	int		status;

	if (!prepare_builtin_execution(cmd, &stdout_backup))
		return (1);
	pid = create_builtin_process(cmd, shell);
	if (pid == -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	return (handle_wait_status(status));
}

int	prepare_builtin_execution(t_command *cmd, int *stdout_backup)
{
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdout_backup == -1)
	{
		perror("minishell");
		return (0);
	}
	if (!exec_redirections(cmd))
	{
		dup2(*stdout_backup, STDOUT_FILENO);
		close(*stdout_backup);
		g_exitcode = 1;
		return (0);
	}
	return (1);
}
