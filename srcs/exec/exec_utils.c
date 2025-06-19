/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:21:55 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 01:15:11 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_pipe(t_command *cmd)
{
	if (!cmd)
		return (0);
	return (cmd && cmd->next != NULL);
}

char	*handle_command_not_found(char *cmd)
{
	write(2, "matteoshell: ", 13);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	g_exitcode = 127;
	return (NULL);
}

void	init_heredoc_fds(t_command *cmd)
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
			{
				current_redir->heredoc_fd = handle_heredoc(
						current_redir->filename);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

int	check_output_redirection(t_command *cmd)
{
	t_redirection	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_wait_status(int status)
{
	setup_shell_signals();
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		g_exitcode = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	else
		g_exitcode = 1;
	return (g_exitcode);
}
