#include "../../inc/minishell.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

// DOIT CHANGER TOUS LES MSG + LES EXITS CODE
// Ouvre le fichier en mode écriture (append ou truncate selon le flag)
// O_TRUNC => Ecrase le fichier s'il existe, sinon il le cree
// O_APPEND => lui ajoute a la fin du fichier ou le creer si il existe pas

static int open_outfile(const char *output_file, int append_flag)
{
	int	fd;

	if (append_flag)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

// <
/* static int handle_input_redirection(const char *input_file)
{
    
    return (1);
}
 */

int	handle_heredoc(const char *delimiter)
{
	int		pipefd[2];
	char	*line;
	size_t	delimiter_length;
	int		result_fd;

	if (pipe(pipefd) == -1)
	{
		write(2, "minishell: pipe error\n", 22);
		return (-1);
	}
	delimiter_length = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == delimiter_length && ft_strncmp(line, delimiter, delimiter_length) == 0))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	result_fd = pipefd[0];
	return (result_fd);
}

int	exec_redirections(t_command *cmd)
{
	t_redirection *redirection;
	t_redirection *last_out;
	t_redirection *last_in;
	t_redirection *tmp;
	int fd;
    int append_flag;

    redirection = cmd->redirection;
    last_out = NULL;
    last_in = NULL;
	tmp = redirection;
    append_flag = 0;
    // On cherche la derniere redirection de chaque type
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
			last_out = tmp;
		if (tmp->type == IN)
			last_in = tmp;
		tmp = tmp->next;
	}
	// On applique toutes les redirections dans l'ordre
	tmp = redirection;
	while (tmp)
	{
		if (tmp->type == OUT || tmp->type == APPEND)
		{
			if (tmp->type == APPEND)
				append_flag = 1;
			else
				append_flag = 0;
			fd = open_outfile(tmp->filename, append_flag);
			if (fd < 0)
			{
				write(2, "redirection error\n", 18);
				return (0);
			}
			// dup2(int newfd, int oldfd) (= ecris desormais dans le fichier fd a la place de 1/stdout(le terminal)/ le 2eme argument)
			if (tmp == last_out)
			{
				if (dup2(fd, STDOUT_FILENO) < 0)
				{
					write(2, "dup2 error\n", 12);
					close(fd);
					return (0);
				}
			}
			close(fd);
		}
		else if (tmp->type == IN)
		{
			fd = open(tmp->filename, O_RDONLY);
			if (fd < 0)
			{
				write(2, "redirection error\n", 18);
				return (0);
			}
			if (tmp == last_in) // onm dup2 que sur le dernier, les autres c'est juste pour creer et ecraser
			{
				if (dup2(fd, STDIN_FILENO) < 0)
				{
					write(2, "dup2 error\n", 12);
					close(fd);
					return (0);
				}
			}
			close(fd);
		}
		else if (tmp->type == HEREDOC)
		{
			fd = tmp->heredoc_fd;
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
		}
		tmp = tmp->next;
	}
	return (1);
}

