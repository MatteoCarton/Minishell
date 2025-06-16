#include "../../inc/minishell.h"

/* si execve reussit, il remplace tout le code par la fonction choisis, donc perror etc ne seront
jamais execute (sauf si ca fail) */
static void	exec_child_process(char *path, t_command *cmd, t_shell *shell)
{
	execve(path, cmd->args, shell->env);
	perror("minishell");
	exit(127);
}

static char	*get_exec_path(char *cmd, char **env, t_shell *shell)
{
	char	*path;

	path = find_command_path(cmd, env);
	if (!path)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		shell->exit = 127;
		return (NULL);
	}
	return (path);
}

static int	is_builtin(char *arg)
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
	(void)shell; // A SUPPRIMER
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (ft_exit(cmd->args, shell), -1);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (ft_echo(cmd->args), 1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (ft_pwd(), 1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (ft_cd(cmd->args, shell), 1);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (ft_env(shell->env), 1);
	if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (unset_env(cmd->args, &shell->env, cmd->args[1], &shell->exit),
			1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (export_env(cmd->args, &shell->env, cmd->args[1], &shell->exit),
			1);
	return (0);
}

int	exec(t_command *cmd, t_shell *shell)
{
	pid_t pid;
	char *path;
	int status;
	int result;
	int saved_stdout;
	t_redirection *tmp;
	int has_output_redirection;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);

    saved_stdout = -1;
    has_output_redirection = 0;
	// Check s'il y a une redirection de sortie (OUT ou APPEND pour l'instant)
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
			saved_stdout = dup(STDOUT_FILENO);
		if (!exec_redirections(cmd))
		{
			if (saved_stdout != -1)
			{
				dup2(saved_stdout, STDOUT_FILENO);
				close(saved_stdout);
			}
			return (1);
		}
		result = execute_builtin(cmd, shell);
		if (saved_stdout != -1)
		{
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdout);
		}
		return (result);
	}

	path = get_exec_path(cmd->args[0], shell->env, shell);
	if (!path)
		return (127);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		shell->exit = 1;
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		exec_redirections(cmd);
		exec_child_process(path, cmd, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit = WEXITSTATUS(status);
	else
		shell->exit = 1;
	free(path);
	return (shell->exit);
}