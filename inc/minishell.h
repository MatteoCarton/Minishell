#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef EXTRA_CHAR
#  define EXTRA_CHAR "!#$%&()*+,-./:;=?@[\\]^_`{|}~"
# endif

typedef enum s_token_type
{
	END_TOKEN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	IN,
	OUT,
	WORD,
	APPEND,  // >>
	HEREDOC, // <<
	DOLLAR,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**env;
	int				exit;
}					t_shell;

typedef struct s_command
{
	char **args;            // Arguments de la commande
	char *input_file;       // <
	char *output_file;      // > ou >>
	int append;            
		// flag pour >> (append) 0 : "ecrase le fichier" (>), 1 : "ajoute a la fin" (>>)
	char *delimiter;        // Pour << (exemple EOF)
	char *heredoc;          // le contenu qu'on ecrit
	struct s_command *next; // Pour les pipes (on pointera vers la cmd suivante)
}					t_command;

// Signal handling
void				setup_shell_signals(void);
void				setup_child_signals(void);

// SIGNAL
// void handle_signal(int sig);
char				*ft_strdup(const char *s);
t_token				*create_token(t_token_type type, char *str);

// TOKEN
t_token				*create_token(t_token_type type, char *str);
t_token				*get_token(char *line);
void				other_token(char *str, t_token **head, t_token **actual,
						int *i);
void				quotes_token(char *str, t_token **head, t_token **actual,
						int *i);
void				in_out_token(char *str, t_token **head, t_token **actual,
						int *i);
void				pipe_token(char *line, t_token **head, t_token **actual,
						int *i);
int					check_quotes(char *line);
int					is_valid_word(char c);
void				printoken(t_token *head);
void				add_token(t_token **head, t_token **actual, t_token *new);
t_token				*create_token(t_token_type type, char *str);
char				*ft_substr(const char *s, unsigned int start, size_t len);
void				free_token(t_token **head);
void				free_env(char **env);
void				clean_token(t_token *token);

// EXPAND $

void				update_quotes_state(char c, int *in_single, int *in_double);
void				expand_dollar(char **str, t_shell g_env);
int					joignable(char **str, char **new_str, t_shell g_env, int *i,
						int in_single);
void				replace_dollar(char **str, char **new_str, t_shell g_env,
						int *i);
char				*get_var_name(char *str);
char				*join_char(char *s, char c);
char				*join_str(char *s1, char *s2);
char				*ft_itoa(int n);

t_command			*parse_tokens(t_token *tokens);
void				free_command(t_command *cmd);

// EXEC
int					execute_builtin(t_command *cmd, t_shell *shell);

// BUILTINS
void				ft_pwd(void);
void				ft_env(char **envp);
void				ft_echo(char **args);
void				ft_exit(char **args, t_shell *shell);
void				ft_cd(char **args, t_shell *shell);
char				*update_old_pwd_env(char **env);
int					update_new_pwd_env(char **env, const char *old_pwd,
						const char *path);
void				export_env(char **arg, char ***env, char *var_str,
						int *exit);
void				unset_env(char **arg, char ***env, char *var_str,
						int *exit);
// Builtin utils
int					check_line(char ***env, char *str);
char				*get_key(char *str);
int					equal_pos(char *str);
void				show_env(char **env);
char				*get_quoted(char *env);
int	number_of_args(char **args);

#endif