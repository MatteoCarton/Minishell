/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:06:06 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 23:32:22 by mcarton          ###   ########.fr       */
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

/* main.c */
char						**cpy_env(char **envp);

/* shell/shell_utils.c */
void						cleanup_shell_resources(t_shell *shell,
								int stdin_backup);
int							setup_shell_stdin(int stdin_backup,
								int *current_stdin);
int							process_shell_line(char *line, t_shell *shell,
								int stdin_backup);
int							is_only_spaces(char *str);

/* shell/shell_exec.c */
int							start(char **line, t_shell *m);
int							handle_tokens(t_token *lexed, t_shell *m);
int							handle_command(t_command *cmd, t_shell *m,
								t_token *lexed);

/* signal/signal.c */
void						setup_shell_signals(void);
void						setup_child_signals(void);

/* parser/parser.c */
void						handle_argument(t_command *cmd, t_token *current);
t_command					*handle_pipe(t_command *cmd);
int							handle_redirection(t_command *cmd,
								t_token *current);
int							parse_while(t_command **cmd, t_command **first_cmd,
								t_token **current);
t_command					*parse_tokens(t_token *tokens);

/* parser/parser_utils.c */
t_redirection				*add_redirection(t_redirection **redirection_list,
								t_token_type type, char *filename);
t_command					*init_command(void);
void						arg_while(t_command **cmd, char **arg,
								char ***new_args);
void						add_argument(t_command *cmd, char *arg);

/* parser/parser_free.c */
void						free_redirections(t_redirection *redir);
void						free_command(t_command *cmd);

/* lexer/lexer.c */
t_token						*get_token(char *line);
void						check_token(char *line, t_token **head,
								t_token **actual, int *i);
void						word_token(char *str, t_token **head,
								t_token **actual, int *i);
void						process_word_quotes(char *str, char *buff, int *i,
								int *j);
int							is_valid_word(char c);

/* lexer/lexer_token.c */
void						pipe_token(char *line, t_token **head,
								t_token **actual, int *i);
void						in_out_token(char *str, t_token **head,
								t_token **actual, int *i);
t_token						*handle_redirect_in(char *str, int *i);
t_token						*handle_redirect_out(char *str, int *i);
void						quotes_token(char *str, t_token **head,
								t_token **actual, int *i);

/* lexer/lexer_utils.c */
t_token						*create_token(t_token_type type, char *str);
void						add_token(t_token **head, t_token **actual,
								t_token *new);
void						other_token(char *str, t_token **head,
								t_token **actual, int *i);
void						process_quotes(char *str, char *buff, int *i,
								int *j);
int							check_quotes(char *line);

/* lexer/lexer_free.c */
void						free_env(char **env);
void						clean_token(t_token *token);
void						free_token(t_token **head);
void						printoken(t_token *head);

/* expend/expender.c */
int							joignable(char **str, char **new_str, t_shell g_env,
								int *i);
int							process_char(char **str, char **new_str,
								t_shell g_env, int *i);
int							add_single_quote_char(char **str, char **new_str,
								int *i);
int							expand_dollar_loop(char **str, char **new_str,
								t_shell g_env);
void						expand_dollar(char **str, t_shell g_env);

/* expend/expender_env.c */
char						*find_env_value(char **env, char *var);
char						*get_var_name(char *str);
char						*handle_env_var(char **str, t_shell g_env, int *i);
char						*get_replacement_value(char **str, t_shell g_env,
								int *i);
void						replace_dollar(char **str, char **new_str,
								t_shell g_env, int *i);

/* expend/expender_utils.c */
void						update_quotes_state(char c, int *in_single,
								int *in_double);
char						*join_str(char *s1, char *s2);
char						*join_char(char *s, char c);
int							len(long nbr);
char						*ft_itoa(int n);

/* exec/exec_path.c */
void						print_file_error(const char *path,
								const char *error_msg);
int							check_file_exists(const char *path);
int							check_file_permissions(const char *path);
char						*handle_absolute_path(char *cmd);
char						*get_exec_path(char *cmd, char **env);

/* exec/exec_utils.c */
int							has_pipe(t_command *cmd);
char						*handle_command_not_found(char *cmd);
void						init_heredoc_fds(t_command *cmd);
int							check_output_redirection(t_command *cmd);
int							handle_wait_status(int status);

/* exec/exec_main.c */
int							check_is_directory(const char *path);
int							prepare_command_execution(t_command *cmd,
								t_shell *shell, int *stdout_backup,
								char **path);
int							handle_builtin_no_redir(t_command *cmd,
								t_shell *shell, int stdout_backup);
int							handle_simple_command(t_command *cmd,
								t_shell *shell);
int							exec(t_command *cmd, t_shell *shell);

/* exec/exec_external.c */
void						exec_child_process(char *path, t_command *cmd,
								t_shell *shell);
int							setup_external_exec(t_command *cmd, t_shell *shell,
								char **path);
int							handle_external_child(char *path, t_command *cmd,
								t_shell *shell);
int							create_child_exec(char *path, t_command *cmd,
								t_shell *shell, int stdout_backup);
int							exec_external_command(t_command *cmd,
								t_shell *shell);

/* exec/exec_builtin.c */
int							is_builtin(char *arg);
int							execute_builtin(t_command *cmd, t_shell *shell);
int							create_builtin_process(t_command *cmd,
								t_shell *shell);
int							exec_builtin_with_fork(t_command *cmd,
								t_shell *shell);
int							prepare_builtin_execution(t_command *cmd,
								int *stdout_backup);

/* exec/exec_find_path.c*/
char						*find_command_path(char *cmd, char **env);
void						free_tab(char **tab);

/* exec/pipe_main.c*/
void						wait_all_children(int n_cmd);
int							init_pipe_data(t_command *cmd, int **pipes,
								int *n_pipes, int *n_cmd);
int							fork_children(t_command *cmd, int *pipes,
								t_shell *shell);
int							exec_pipe(t_command *cmd, t_shell *shell);

/* exec/pipe_child.c*/
void						handle_child_redirections_and_exit(t_command *cmd,
								int *pipes, int index, int n_pipes);
void						execute_child_builtin_or_cmd(t_command *cmd,
								t_shell *shell);
void						execute_child_pipe(t_command *cmd, int *pipes,
								int index, t_shell *shell);
/* exec/pipe_utils.c*/
int							count_pipes(t_command *cmd);
void						setup_pipe_redirections(int *pipes, int index,
								int n_pipes);
int							alloc_pipe_array(int **pipes, int n_pipes);
int							create_pipes(int *pipes, int n_pipes);

/* exec/redirections_out.c */
int							open_outfile(const char *output_file,
								int append_flag);
int							try_open_outfile(t_redirection *redir, int *fd);
int							handle_redir_out(t_redirection *redir);

/* exec/redirections_in.c */
int							try_open_infile(t_redirection *redir, int *fd);
int							try_dup2_infile(int fd);
int							handle_redir_in(t_redirection *redir,
								t_redirection *last_in);
int							handle_heredoc(const char *delimiter);
int							write_heredoc_lines(int write_fd,
								const char *delimiter, size_t delimiter_length);

/* exec/redirections_apply.c */
void						find_last_redirs(t_redirection *redirection,
								t_redirection **last_out,
								t_redirection **last_in);
int							apply_redirections(t_redirection *redirection,
								t_redirection *last_in);
int							exec_redirections(t_command *cmd);
int							handle_redir_heredoc(t_redirection *redir);

/* exec/builtin/builtin_utils.c */
int							number_of_args(char **args);
char						*ft_strcpy(char *dest, const char *src);

/* exec/builtin/ft_cd.c */
void						change_directory(char *arg1, t_shell *shell);
void						ft_cd(char **args, t_shell *shell);

/* exec/builtin/ft_cd2.c */
void						update_env_var(char **env, const char *name,
								const char *value);
char						*update_old_pwd_env(char **env);
int							update_new_pwd_env(char **env, const char *old_pwd,
								const char *path);

/* exec/builtin/ft_echo.c */
int							ft_echo(char **args);

/* exec/builtin/ft_env.c */
void						ft_env(char **envp);

/* exec/builtin/ft_exit.c */
int							overflow_positive(long long result, int digit,
								const char *str);
int							overflow_negative(long long result, int digit,
								const char *str);
int							overflow_or_not(long long result, int digit,
								bool plus_sign, const char *str);
int							handle_exit_errors(char **args);
int							ft_exit(char **args);

/* exec/builtin/ft_exit2.c */
bool						handle_sign(const char *str, int *i);
bool						is_numeric(char *arg);
int							ft_atoi_with_overflow(const char *str, int *error);

/* exec/builtin/ft_export.c */
void						add_env_var(char ***env, char *str);
void						fill_export_output(char ***env, char **output,
								int i);
void						all_export(char ***env);
void						export_with_args(char **arg, char ***env,
								int *exit);
void						export_env(char **arg, char ***env, int *exit);

/* exec/builtin/ft_export2.c */
char						*get_key(char *str);
int							check_line(char ***env, char *str);
int							equal_pos(char *str);
void						show_env(char **env);
char						*get_quoted(char *env);

/* exec/builtin/ft_export3.c */
int							valid_env(char *str);

/* exec/builtin/ft_pwd.c */
void						ft_pwd(void);

/* exec/builtin/ft_unset.c */
void						remove_line(char ***env, int unset);
int							get_line_unset(char **env, char *unset);
void						unset_env(char **arg, char ***env, char *var_str,
								int *exit);

#endif