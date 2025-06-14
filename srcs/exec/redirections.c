#include "../../inc/minishell.h"

static int	open_outfile(const char *output_file, int append_flag)
{
	int	fd;

	if (append_flag)
		fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

// dup2(int oldfd, int newfd) (= ecris desormais dans le fichier fd a la place de 1/stdout(le terminal))
static int	handle_output_redirection(const char *output_file, int append_flag)
{
	int	fd;

	/* Ouvre le fichier en mode ecriture (append ou truncate selon le flag) */
	fd = open_outfile(output_file, append_flag);
	if (fd < 0)
	{
        // A FAIRE METTRE LE VRAI MESSAGE BASH + RENVOYER L'EXIT CODE !!!
        // A FAIRE METTRE LE VRAI MESSAGE BASH + RENVOYER L'EXIT CODE !!!
		perror("minishell: open (output redirection)"); 
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
        // A FAIRE METTRE LE VRAI MESSAGE BASH + RENVOYER L'EXIT CODE !!!
        // A FAIRE METTRE LE VRAI MESSAGE BASH + RENVOYER L'EXIT CODE !!!
		perror("minishell: dup2 (output redirection)");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

// <
/* static int handle_input_redirection(const char *input_file)
{
    
    return (1);
}
 */
int	exec_redirections(t_command *cmd)
{
    if (cmd->output_file)
        handle_output_redirection(cmd->output_file, cmd->append);
    // if (cmd->input_file)
        // handle_input_redirection(cmd->input_file);
    return (1);
}

