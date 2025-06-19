/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:41:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 11:16:31 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	write_heredoc_lines(int write_fd, const char *delimiter,
		size_t delimiter_length)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == delimiter_length && ft_strncmp(line,
					delimiter, delimiter_length) == 0))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_heredoc(const char *delimiter)
{
	int		pipefd[2];
	size_t	delimiter_length;
	int		result_fd;

	if (pipe(pipefd) == -1)
	{
		write(2, "minishell: pipe error\n", 22);
		return (-1);
	}
	delimiter_length = ft_strlen(delimiter);
	write_heredoc_lines(pipefd[1], delimiter, delimiter_length);
	close(pipefd[1]);
	result_fd = pipefd[0];
	return (result_fd);
}

int	try_open_infile(t_redirection *redir, int *fd)
{
	*fd = open(redir->filename, O_RDONLY);
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

int	try_dup2_infile(int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		write(2, "minishell: ", 11);
		perror("dup2");
		close(fd);
		g_exitcode = 1;
		return (0);
	}
	return (1);
}

int	handle_redir_in(t_redirection *redir, t_redirection *last_in)
{
	int	fd;

	if (!try_open_infile(redir, &fd))
		return (0);
	if (redir == last_in)
	{
		if (!try_dup2_infile(fd))
			return (0);
	}
	close(fd);
	return (1);
}
