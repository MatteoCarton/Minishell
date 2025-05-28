/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:54:33 by alama             #+#    #+#             */
/*   Updated: 2025/01/17 13:19:34 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXE_H
# define FT_EXE_H

# include "mini_shell.h"

typedef struct s_pipe
{
	t_node	*left;
	t_node	*right;
	int		child1;
	int		child2;
	int		status;
	int		end[2];
}			t_pipe;

typedef struct s_dir
{
	int		fd;
	int		pid;
	int		status;
	char	*trim;
}			t_dir;

void		ft_print(char *str);
void		set_ctxt(t_ctxt *ctxt);
int			ft_exe(t_node *node, char **envp);
char		*find_path(char **envp, char **cmd);
void		ft_free_str(char **str);
void		pipex(t_node *node, char **envp, t_ctxt *ctxt);
void		pipe_right(t_node *right, t_node *left, char **envp);
void		pipe_left(t_node *right, t_node *left, char **envp);
void		input_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void		output_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void		output_append(t_node *right, t_node *left, char **envp,
				t_ctxt *ctxt);
int			first_process(t_node *node, char **envp);
void		di_to_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt);
void		exe_pipe(t_node *node, char **envp, t_ctxt *ctxt);
void		split_for_exe(t_node *node);
void		add_space_split(char **data);
void		remove_quote(char **data);
void		ft_exe_dir(t_node *node, char **env, t_ctxt *ctxt);
void		dir_process(t_node *node, char **env, t_ctxt *ctxt);
char		*trim_file(t_node *node);
void		fd_err(char **str);
void		fork_err_dir(char **str);
void		child_input(t_dir *dir, t_ctxt *ctxt, t_node *left, char **envp);
void		child_output(t_dir *dir, t_ctxt *ctxt, t_node *left, char **envp);
void		ft_execv_error(char **split_cmd);
char		**init_string_process(t_node *node);
void		ft_execv(char **split_cmd, char **env, int is_child);
t_token		*inside_tokenize(int *i, char *str, t_token *tok);

#endif
