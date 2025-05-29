#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

extern int g_excode; // stock le code de sortie du shell 

typedef enum s_token_type
{
	END_TOKEN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	IN,
	OUT,
	DOLLAR,
    WORD,
    APPEND, // >>
    HEREDOC, // <<
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}					t_token;


typedef struct s_command
{
    char **args;           // Arguments de la commande
    char *input_file;      // <
    char *output_file;     // > ou >>
    int append;            // flag pour >> (append) 0 : "ecrase le fichier" (>), 1 : "ajoute a la fin" (>>)
    char *delimiter;       // Pour << (exemple EOF)
    char *heredoc;         // le contenu qu'on ecrit
    struct s_command *next; // Pour les pipes (on pointera vers la cmd suivante)
} t_command;

// Signal handling
void setup_shell_signals(void);
void setup_child_signals(void);

// SIGNAL
void handle_signal(int sig);

#endif