#include "../../inc/minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// DOIT CHANGER TOUS LES MSG + LES EXITS CODE
// Ouvre le fichier en mode écriture (append ou truncate selon le flag)
// O_TRUNC => Ecrase le fichier s'il existe, sinon il le cree
// O_APPEND => lui ajoute a la fin du fichier ou le creer si il existe pas

static int	open_outfile(const char *output_file, int append_flag)
{
	int	fd;

	if (append_flag)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

static int	write_heredoc_lines(int write_fd, const char *delimiter,
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

static int	handle_redir_out(t_redirection *redir, t_redirection *last_out)
{
	int	fd;
	int	append_flag;

	append_flag = 0;
	if (redir->type == APPEND)
		append_flag = 1;
	fd = open_outfile(redir->filename, append_flag);
	if (fd < 0)
	{
		write(2, "redirection error\n", 18);
		return (0);
	}
	if (redir == last_out)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			write(2, "dup2 error\n", 12);
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

static int	handle_redir_in(t_redirection *redir, t_redirection *last_in)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "redirection error\n", 18);
		return (0);
	}
	if (redir == last_in)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			write(2, "dup2 error\n", 12);
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

static int	handle_redir_heredoc(t_redirection *redir)
{
	int	fd;

	fd = redir->heredoc_fd;
	if (fd < 0)
	{
		write(2, "heredoc error\n", 14);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		write(2, "dup2 error\n", 12);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static void	find_last_redirs(t_redirection *redirection,
		t_redirection **last_out, t_redirection **last_in)
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

static int	apply_redirections(t_redirection *redirection,
		t_redirection *last_out, t_redirection *last_in)
{
	t_redirection	*tmp;

	tmp = redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
		{
			if (!handle_redir_out(tmp, last_out))
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
	return (apply_redirections(cmd->redirection, last_out, last_in));
}
