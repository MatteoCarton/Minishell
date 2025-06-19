/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:13:11 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 23:32:30 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cleanup_shell_resources(t_shell *shell, int stdin_backup)
{
	free_env(shell->env);
	rl_clear_history();
	close(stdin_backup);
}

int	setup_shell_stdin(int stdin_backup, int *current_stdin)
{
	*current_stdin = dup(STDIN_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	return (*current_stdin);
}

int	process_shell_line(char *line, t_shell *shell, int stdin_backup)
{
	int	result;

	if (*line && !is_only_spaces(line))
	{
		add_history(line);
		result = start(&line, shell);
		free(line);
		if (result == -19)
		{
			cleanup_shell_resources(shell, stdin_backup);
			exit(g_exitcode);
		}
	}
	else
		free(line);
	return (0);
}

int	is_only_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}
