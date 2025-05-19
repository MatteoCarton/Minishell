#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_cmd
{
    char    *cmd;       // la commande
    char    **args;     // tableau d'argument (le -n de echo par exemple)
    int     argc;       // nombre d'arguments
} t_cmd;

// parsing
t_cmd   *parse_cmd(char *line);
int     copy_command(t_cmd *cmd, char *line);
int     copy_arguments(t_cmd *cmd, char *line);

// utils
int     is_whitespace(char c);
int     is_in_quotes(char *line, int i);
int	    handle_whitespace(char *line, int *i, int *start);

#endif