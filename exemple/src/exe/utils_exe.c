/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:14:44 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 16:12:52 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**init_string_process(t_node *node)
{
	t_node	*tmp;
	char	**split_cmd;

	tmp = node;
	split_for_exe(tmp);
	split_cmd = ft_split(tmp->data.str, ' ');
	add_space_split(split_cmd);
	remove_quote(split_cmd);
	return (split_cmd);
}

void	ft_execv(char **split_cmd, char **env, int is_child)
{
	char	*path;

	if (is_child == 0)
		child_signals();
	path = find_path(env, split_cmd);
	child_signals();
	g_excode = execve(path, split_cmd, env);
	ft_execv_error(split_cmd);
}

void	set_ctxt(t_ctxt *ctxt)
{
	ctxt->infile = 0;
	ctxt->outfile = 1;
	ctxt->end[0] = -1;
	ctxt->end[1] = -1;
	ctxt->is_first_o = 0;
	ctxt->is_first_i = 0;
}
