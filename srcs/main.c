/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:12:50 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 13:59:09 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			g_exitcode = 0;

static char	**cpy_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = strdup(envp[i]);
		if (!env[i])
		{
			while (i-- > 0)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

static int	init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return (0);
	shell->env = cpy_env(envp);
	if (!shell->env)
		return (0);
	setup_shell_signals();
	return (1);
}

static int	handle_shell_input(t_shell *shell, int stdin_backup,
		int *current_stdin)
{
	char	*line;

	if (setup_shell_stdin(stdin_backup, current_stdin) == -1)
		return (0);
	dup2(stdin_backup, STDIN_FILENO);
	line = readline("matteoshell$ ");
	dup2(*current_stdin, STDIN_FILENO);
	close(*current_stdin);
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	process_shell_line(line, shell, stdin_backup);
	return (1);
}

static void	run_shell(t_shell *shell)
{
	int		stdin_backup;
	int		current_stdin;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
	{
		perror("matteoshell");
		exit(1);
	}
	while (19)
	{
		if (!handle_shell_input(shell, stdin_backup, &current_stdin))
			break ;
	}
	cleanup_shell_resources(shell, stdin_backup);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		return (0);
	if (init_shell(&shell, envp) == 0)
		return (1);
	run_shell(&shell);
	return (g_exitcode);
}
