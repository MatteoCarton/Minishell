/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:58:05 by alama             #+#    #+#             */
/*   Updated: 2025/01/20 16:42:09 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	exec_builtin(char **args, char **env)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args), -1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args), 1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args), 1);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(args, env), 1);
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, &env), 1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd(args), 1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, &env), 1);
	return (0);
}

int	first_process(t_node *node, char **env)
{
	char	**split_cmd;
	int		pid;
	int		status;

	split_cmd = init_string_process(node);
	status = exec_builtin(split_cmd, env);
	if (status != 0)
	{
		ft_free_str(split_cmd);
		if (status == -1)
			return (-1);
		return (1);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork fails\n"), 0);
	if (pid == 0)
		ft_execv(split_cmd, env, 0);
	waitpid(pid, &status, 0);
	initialize_signals();
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
	ft_free_str(split_cmd);
	return (0);
}

void	dir_process(t_node *node, char **env, t_ctxt *ctxt)
{
	char	**split_cmd;

	split_cmd = init_string_process(node);
	child_signals();
	if (ctxt->infile != 0)
	{
		dup2(ctxt->infile, STDIN_FILENO);
		close(ctxt->infile);
	}
	if (ctxt->outfile != 1)
	{
		dup2(ctxt->outfile, STDOUT_FILENO);
		close(ctxt->outfile);
	}
	if (exec_builtin(split_cmd, env))
	{
		ft_free_str(split_cmd);
		exit(g_excode);
	}
	ft_execv(split_cmd, env, 1);
}

int	handle_str_node(t_node *node, char **env)
{
	if (ft_strcmp(node->data.str, " ") == 0)
		return (0);
	return (first_process(node, env));
}

int	ft_exe(t_node *node, char **env)
{
	t_node	*left;
	t_node	*right;
	t_ctxt	ctxt;
	int		exit;

	set_ctxt(&ctxt);
	if (node->type == STR_NODE)
		exit = handle_str_node(node, env);
	else if (node->type == PAIR_NODE)
	{
		left = node->data.pair.left;
		right = node->data.pair.right;
		if (node->data.pair.opera[0] == '|')
			exe_pipe(node, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
			input_dir(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
			output_dir(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
			output_append(right, left, env, &ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
			di_to_dir(right, left, env, &ctxt);
	}
	return (exit);
}
