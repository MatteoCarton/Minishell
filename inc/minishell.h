/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:06:06 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 18:35:37 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef EXTRA_CHAR
#  define EXTRA_CHAR "!#$%&()*+,-./:;=?@[\\]^_`{|}~"
# endif

extern int					g_exitcode;

typedef enum s_token_type
{
	END_TOKEN,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	IN,
	OUT,
	WORD,
	APPEND,
	HEREDOC,
	DOLLAR,
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*str;
	struct s_token			*next;
}							t_token;

typedef struct s_shell
{
	char					**env;
}							t_shell;

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	int						heredoc_fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char					**args;
	t_redirection			*redirection;
	struct s_command		*next;
}							t_command;

/* shell/shell_utils.c */
void						cleanup_shell_resources(t_shell *shell,
								int stdin_backup);
int							setup_shell_stdin(int stdin_backup,
								int *current_stdin);
int							process_shell_line(char *line, t_shell *shell,
								int stdin_backup);

/* shell/shell_exec.c */
int							start(char **line, t_shell *m);

/* signal/signal.c */
void						setup_shell_signals(void);
void						setup_child_signals(void);

/* parser/parser.c */
t_command					*parse_tokens(t_token *tokens);

/* parser/parser_utils.c */
t_redirection				*add_redirection(t_redirection **redirection_list,
								t_token_type type, char *filename);
t_command					*init_command(void);
void						add_argument(t_command *cmd, char *arg);

/* parser/parser_free.c */
void						free_command(t_command *cmd);
t_command					*handle_pipe(t_command *cmd);

/* lexer/lexer.c */
t_token						*get_token(char *line);
void						word_token(char *str, t_token **head,
								t_token **actual, int *i);
void						process_word_quotes(char *str, char *buff, int *i,
								int *j);

/* lexer/lexer_token.c */
void						pipe_token(char *line, t_token **head,
								t_token **actual, int *i);
void						in_out_token(char *str, t_token **head,
								t_token **actual, int *i);
void						quotes_token(char *str, t_token **head,
								t_token **actual, int *i);

/* lexer/lexer_utils.c */
t_token						*create_token(t_token_type type, char *str);
void						add_token(t_token **head, t_token **actual,
								t_token *new);
void						process_quotes(char *str, char *buff, int *i,
								int *j);
int							check_quotes(char *line);

/* lexer/lexer_free.c */
void						free_env(char **env);
void						free_token(t_token **head);

/* expend/expender.c */
void						expand_dollar(char **str, t_shell g_env);

/* expend/expender_env.c */
char						*find_env_value(char **env, char *var);
void						replace_dollar(char **str, char **new_str,
								t_shell g_env, int *i);

/* expend/expender_utils.c */
void						update_quotes_state(char c, int *in_single,
								int *in_double);
char						*join_str(char *s1, char *s2);
char						*join_char(char *s, char c);
char						*ft_itoa(int n);

/* exec/exec_path.c */
void						print_file_error(const char *path,
								const char *error_msg);
char						*get_exec_path(char *cmd, char **env);

/* exec/exec_utils.c */
char						*handle_command_not_found(char *cmd);
void						init_heredoc_fds(t_command *cmd);
int							check_output_redirection(t_command *cmd);
int							handle_wait_status(int status);

/* exec/exec_main.c */
int							check_is_directory(const char *path);
int							prepare_command_execution(t_command *cmd,
								t_shell *shell, int *stdout_backup,
								char **path);
int							exec(t_command *cmd, t_shell *shell);

/* exec/exec_external.c */
int							setup_external_exec(t_command *cmd, t_shell *shell,
								char **path);
int							exec_external_command(t_command *cmd,
								t_shell *shell);

/* exec/exec_builtin.c */
int							is_builtin(char *arg);
int							execute_builtin(t_command *cmd, t_shell *shell);
int							exec_builtin_with_fork(t_command *cmd,
								t_shell *shell);

/* exec/exec_find_path.c*/
char						*find_command_path(char *cmd, char **env);

/* exec/pipe_main.c*/
void						wait_all_children(int n_cmd, pid_t *pids);
int							exec_pipe(t_command *cmd, t_shell *shell);

/* exec/pipe_child.c*/
void						execute_child_pipe(t_command *cmd, int *pipes,
								int index, t_shell *shell);
void						parent_close_fds(int *pipes, int i, int n_pipes);
void						parent_cleanup(int *pipes, int n_pipes, int n_cmd,
								pid_t *pids);

/* exec/pipe_utils.c*/
int							count_pipes(t_command *cmd);
void						setup_pipe_redirections(int *pipes, int index,
								int n_pipes);
int							alloc_pipe_array(int **pipes, int n_pipes);
int							create_pipes(int *pipes, int n_pipes);
void						update_last_status(int status, int *last_status);

/* exec/redirections_out.c */
int							handle_redir_out(t_redirection *redir);

/* exec/redirections_in.c */
int							handle_redir_in(t_redirection *redir,
								t_redirection *last_in);
int							handle_heredoc(const char *delimiter);

/* exec/redirections_apply.c */
int							exec_redirections(t_command *cmd);

/* exec/builtin/builtin_utils.c */
int							number_of_args(char **args);

/* exec/builtin/ft_cd_utils.c */
char						*ft_strjoin_path(char const *str1,
								char const *str2);
char						*normalize_path(const char *path);
void						update_pwd_vars(t_shell *shell,
								const char *new_pwd);

/* exec/builtin/ft_cd.c */
void						ft_cd(char **args, t_shell *shell);
void						update_env_var(char **env, const char *name,
								const char *value);

/* exec/builtin/ft_cd2.c */
void						free_components(char **components);
void						fill_path_list(t_list **path_list,
								char **components);
char						*ft_lst_to_path(t_list *lst);

/* exec/builtin/ft_echo.c */
int							ft_echo(char **args);

/* exec/builtin/ft_env.c */
void						ft_env(char **envp);

/* exec/builtin/ft_exit.c */
int							overflow_or_not(long long result, int digit,
								bool plus_sign, const char *str);
int							ft_exit(char **args);

/* exec/builtin/ft_exit2.c */
bool						is_numeric(char *arg);
int							ft_atoi_with_overflow(const char *str, int *error);

/* exec/builtin/ft_export.c */
void						export_env(char **arg, char ***env, int *exit);

/* exec/builtin/ft_export2.c */
int							check_line(char ***env, char *str);
void						show_env(char **env);
char						*get_quoted(char *env);

/* exec/builtin/ft_export3.c */
int							valid_env(char *str);

/* exec/builtin/ft_pwd.c */
void						ft_pwd(t_shell *shell);

/* exec/builtin/ft_unset.c */
void						unset_env(char **arg, char ***env, char *var_str,
								int *exit);

#endif