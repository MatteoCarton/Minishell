#include "../../inc/minishell.h"

/* si execve reussit, il remplace tout le code par la fonction choisis, donc perror etc ne seront
jamais execute (sauf si ca fail) */
int has_pipe(t_command *cmd)
{
    if (!cmd)
        return (0);
    return (cmd && cmd->next != NULL);
}

static void	exec_child_process(char *path, t_command *cmd, t_shell *shell)
{
	execve(path, cmd->args, shell->env);
	perror("minishell");
	exit(127);
}

char	*get_exec_path(char *cmd, char **env)
{
	char	*path;

	path = find_command_path(cmd, env);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		g_exitcode = 127;
		return (NULL);
	}
	return (path);
}

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
		return(ft_exit(cmd->args));
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
		return (unset_env(cmd->args, &shell->env, cmd->args[1], &g_exitcode), g_exitcode);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (export_env(cmd->args, &shell->env, &g_exitcode), g_exitcode);
	return (0);
}

static void	init_heredoc_fds(t_command *cmd)
{
	t_command		*current_cmd;
	t_redirection	*current_redir;

	current_cmd = cmd;
	while (current_cmd)
	{
		current_redir = current_cmd->redirection;
		while (current_redir)
		{
			if (current_redir->type == HEREDOC)
				current_redir->heredoc_fd = handle_heredoc(current_redir->filename);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

int	exec(t_command *cmd, t_shell *shell)
{
	pid_t pid;
	char *path;
	int status;
	t_redirection *tmp;
	int has_output_redirection;

    if (!cmd)
		return (0);
	init_heredoc_fds(cmd);

	if (cmd && cmd->next)
		return (exec_pipe(cmd, shell));

	if (!cmd->args || !cmd->args[0])
		return (0);

	has_output_redirection = 0;
	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
		{
			has_output_redirection = 1;
			break;
		}
		tmp = tmp->next;
	}

	if (is_builtin(cmd->args[0]))
	{
		if (has_output_redirection)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("minishell: fork");
				g_exitcode = 1;
				return (1);
			}
			if (pid == 0)
			{
				setup_child_signals();
				if (!exec_redirections(cmd))
					return (1);
				return (execute_builtin(cmd, shell));
			}
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &status, 0);
			setup_shell_signals();
			if (WIFSIGNALED(status))
				write(1, "\n", 1);
			if (WIFEXITED(status))
				g_exitcode = WEXITSTATUS(status);
			else
				g_exitcode = 1;
			return (g_exitcode);
		}
		// Pas de redirection : execution dans le parent
		return (execute_builtin(cmd, shell));
	}

	if (!exec_redirections(cmd))
		return (1);

	path = get_exec_path(cmd->args[0], shell->env);
	if (!path)
		return (127);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		g_exitcode = 1;
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		exec_redirections(cmd);
		exec_child_process(path, cmd, shell);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_shell_signals();
	if (WIFSIGNALED(status))
		write(1, "\n", 1);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	else
		g_exitcode = 1;
	free(path);
	return (g_exitcode);
}
