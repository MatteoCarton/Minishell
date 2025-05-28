/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_choice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:37:30 by alama             #+#    #+#             */
/*   Updated: 2025/01/20 15:51:03 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	left_pipe(t_pipe *p, char **envp, t_ctxt *ctxt)
{
	dup2(p->end[1], STDOUT_FILENO);
	close(p->end[0]);
	close(p->end[1]);
	ft_exe_dir(p->left, envp, ctxt);
	exit(g_excode);
}

static void	right_pipe(t_pipe *p, char **envp, t_ctxt *ctxt)
{
	dup2(p->end[0], STDIN_FILENO);
	close(p->end[0]);
	close(p->end[1]);
	ft_exe_dir(p->right, envp, ctxt);
	exit(g_excode);
}

static void	fork_err(void)
{
	perror("fork fails\n");
	exit(1);
}

void	exe_pipe(t_node *node, char **envp, t_ctxt *ctxt)
{
	t_pipe	p;

	p.left = node->data.pair.left;
	p.right = node->data.pair.right;
	pipe(p.end);
	p.child1 = fork();
	if (p.child1 < 0)
		fork_err();
	if (p.child1 == 0)
		left_pipe(&p, envp, ctxt);
	p.child2 = fork();
	if (p.child2 < 0)
		fork_err();
	if (p.child2 == 0)
		right_pipe(&p, envp, ctxt);
	close(p.end[0]);
	close(p.end[1]);
	waitpid(p.child1, &p.status, 0);
	waitpid(p.child2, &p.status, 0);
	if (WIFEXITED(p.status))
		g_excode = WEXITSTATUS(p.status);
	else
		g_excode = 1;
}

void	ft_exe_dir(t_node *node, char **env, t_ctxt *ctxt)
{
	t_node	*left;
	t_node	*right;

	if (node->type == STR_NODE)
		dir_process(node, env, ctxt);
	else if (node->type == PAIR_NODE)
	{
		left = node->data.pair.left;
		right = node->data.pair.right;
		if (node->data.pair.opera[0] == '|')
			exe_pipe(node, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<", 2) == 0)
			input_dir(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">", 2) == 0)
			output_dir(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, ">>", 3) == 0)
			output_append(right, left, env, ctxt);
		else if (ft_strncmp(node->data.pair.opera, "<<", 3) == 0)
			di_to_dir(right, left, env, ctxt);
	}
}
