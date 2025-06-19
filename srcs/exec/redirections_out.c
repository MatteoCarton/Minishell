/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:41:08 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 10:44:11 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_outfile(const char *output_file, int append_flag)
{
	int	fd;

	if (append_flag)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	try_open_outfile(t_redirection *redir, int *fd)
{
	int	append_flag;

	append_flag = 0;
	if (redir->type == APPEND)
		append_flag = 1;
	*fd = open_outfile(redir->filename, append_flag);
	if (*fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, redir->filename, ft_strlen(redir->filename));
		write(2, ": ", 2);
		perror("");
		g_exitcode = 1;
		return (0);
	}
	return (1);
}

int	handle_redir_out(t_redirection *redir)
{
	int	fd;

	if (!try_open_outfile(redir, &fd))
		return (0);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		write(2, "minishell: ", 11);
		perror("dup2");
		close(fd);
		g_exitcode = 1;
		return (0);
	}
	close(fd);
	return (1);
}
