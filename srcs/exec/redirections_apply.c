/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_apply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:39:01 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 17:24:43 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	find_last_redirs(t_redirection *redirection, t_redirection **last_out,
		t_redirection **last_in)
{
	t_redirection	*tmp;

	*last_out = NULL;
	*last_in = NULL;
	tmp = redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
			*last_out = tmp;
		if (tmp->type == IN)
			*last_in = tmp;
		tmp = tmp->next;
	}
}

int	apply_redirections(t_redirection *redirection, t_redirection *last_in)
{
	t_redirection	*tmp;

	tmp = redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
		{
			if (!handle_redir_out(tmp))
				return (0);
		}
		else if (tmp->type == IN)
		{
			if (!handle_redir_in(tmp, last_in))
				return (0);
		}
		else if (tmp->type == HEREDOC)
		{
			if (!handle_redir_heredoc(tmp))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	exec_redirections(t_command *cmd)
{
	t_redirection	*last_out;
	t_redirection	*last_in;

	find_last_redirs(cmd->redirection, &last_out, &last_in);
	return (apply_redirections(cmd->redirection, last_in));
}

int	handle_redir_heredoc(t_redirection *redir)
{
	int	fd;

	fd = redir->heredoc_fd;
	if (fd < 0)
	{
		write(2, "matteoshell: heredoc: ", 22);
		perror("");
		g_exitcode = 1;
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		write(2, "matteoshell: ", 13);
		perror("dup2");
		close(fd);
		g_exitcode = 1;
		return (0);
	}
	close(fd);
	return (1);
}
