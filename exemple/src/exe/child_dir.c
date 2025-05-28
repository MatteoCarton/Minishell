/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:34:55 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 22:58:56 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	child_input(t_dir *dir, t_ctxt *ctxt, t_node *left, char **envp)
{
	if (ctxt->is_first_i == 0)
	{
		ctxt->infile = dir->fd;
		ctxt->is_first_i = 1;
	}
	free(dir->trim);
	dir->trim = NULL;
	ft_exe_dir(left, envp, ctxt);
	exit(g_excode);
}

void	child_output(t_dir *dir, t_ctxt *ctxt, t_node *left, char **envp)
{
	if (ctxt->is_first_o == 0)
	{
		ctxt->outfile = dir->fd;
		ctxt->is_first_o = 1;
	}
	free(dir->trim);
	dir->trim = NULL;
	ft_exe_dir(left, envp, ctxt);
	exit(g_excode);
}
