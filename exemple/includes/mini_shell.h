/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:43 by alama             #+#    #+#             */
/*   Updated: 2025/01/20 16:21:50 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft.h"
# include <stdio.h>
# include "token.h"
# include "ft_exe.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef MINISHELL_H
#  define MINISHELL_H

/* Exit Code */
extern int	g_excode;

/* CHECK ARGS */
void		check_args(int ac, char **av);

/* Error Handling */
void		ft_quit(void);

/* TOKENIZE */
void		ft_add_token(t_token **token, t_token_type type, char *lexeme);
t_token		*tokenize(char *str);

/* PARSING */
t_node		*parse(t_token **token_list);

/* UTILS */
int			only_space(char *str);
void		parent_signals(void);
void		child_signals(void);

/* PRINT UTILS */
void		print_token_list(t_token *token_list);
void		print_node(t_node *node);

/* NODE UTILITIES */
t_node		*parse(t_token **token_list);
void		execute_node(t_node *node);
t_node		*str_node(t_token **token, int pipe);
t_node		*pair_node(t_node *left, t_token **token);
void		ft_free_node(t_node **node);
t_node		*dir_parse(t_token **token);
t_node		*pair_dir(t_node *left, t_token **token);
void		ft_free_all_node(t_node **node);
t_node		*set_right_file(t_token **token, t_node *left);
void		heredoc_parse(t_token **token);
void		set_right_space(t_node *left, t_node *right);
t_node		*one_str(t_token **token);
void		add_dollar(t_node *node, char **env);

/* TOKEN UTILITIES */
void		ft_if_not_last(t_token **token_list, t_token **new_node);
void		ft_add_next(t_token *last, t_token **token_list, t_token *new_node);
int			ft_str_to_lexeme(int i, char *str, t_token **tok,
				t_token_type type);
void		ft_free_token(t_token **token_list);
void		remove_end(t_token **token);
t_token		*last_token(t_token *token);
char		*ft_last_pipe(t_token **token_list, char *str);
int			ft_verrif_tok(t_token **token_list);
int			ft_is_dir(t_token *token);
void		ft_not_close(char c);
int			d_and_s_token(int *i, char *str, t_token **token_list);
t_token		*find_pipe(t_token *token_list);
int			which_token(int *i, char *str, t_token **token_list);
int			ft_is_lexeme(char c);
int			handle_invalid_token(int c);
int			handle_redirection_token(int *i, char *str, t_token **token_list);
int			handle_quotes_token(int *i, char *str, t_token **token_list);
int			handle_parentheses_token(int c);
int			handle_pipe_token(int *i, char *str, t_token **token_list);
int			handle_space_token(int *i, char *str, t_token **token_list);

/* STRING UTILITIES */
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strdel(char *str, const char *del);

void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

/* COMMAND TREE */
t_node		*build_command_tree(t_token *tokens);

/* ENVIRONMENT */
char		**copy_env(char **env);
void		ft_free_env(char **array);

/* Built-in Functions */
void		ft_cd(char **args);
void		ft_echo(char **args);
void		ft_env(char **args, char **env);
void		ft_export(char **args, char ***env);
void		ft_exit(char **args);
void		ft_pwd(char **args);
void		ft_unset(char **args, char ***env);

/* Signal Handlers */
void		handle_sigquit(int sig);
void		handle_sigint(int signal);
void		initialize_signals(void);
void		ft_ctrl_c_child(int signal);

/* ENV NODE REPLACEMENT */
void		replace_env_in_nodes(t_node *node, char **env);

/* STRING CLEANING */
char		*remove_backslashes(const char *str);
void		clean_str_nodes(t_node *node);

/* QUOTE HANDLING */
int			ft_is_valid_n_option(char *arg);
int			ft_numbers_of_singlequotes(char *str);
char		*ft_remove_quotes(const char *str);
int			ft_should_skip_quote(char c, int dq_count, int sq_count);

/* ARRAY HANDLING */
size_t		get_2d_array_size(char **array);
int			is_valid_var_name(char *var);
int			len_arg(char *arg);
int			var_exist(char *arg, char **env);
int			find_var_index(char *arg, char **env);
char		**ft_split_quote(char const *str);

/* ENVIRONMENT VARIABLE MANAGEMENT */
char		*get_env_value(char *var, char **env);
char		*itoa_exit_code(int n);

/* DOLLAR HANDLING */
char		*handle_simple_dollar(char **result);
char		*handle_exit_code(char **result);
char		*handle_dollar(char **result, char *str, int *i, char **env);
char		*add_char_to_result(char *result, char c);
char		*replace_dollar_str(char *str, char **env);
char		*process_chars(char *str, char **env);
int			is_quote(char c, int in_double_quotes, int in_single_quotes);
void		toggle_quote_state(char c, int *in_single_quotes,
				int *in_double_quotes);
char		*handle_quotes_logic(char *result, char c, int *in_single_quotes,
				int *in_double_quotes);
char		*handle_char_logic(char *result, char c);
char		*handle_dollars_logic(char *result, char *str, int *i, char **env);

void		free_all(char **env);

/* STRING ADDITION */
void		ft_add_str(char ***split, const char *str);
int			ft_handle_quote(char const *str, int i);

# endif /* MINISHELL_H */

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}			t_sig;

typedef struct s_quotes
{
	char	*result;
	int		i;
	int		in_single_quotes;
	int		in_double_quotes;
}			t_quotes;

#endif
