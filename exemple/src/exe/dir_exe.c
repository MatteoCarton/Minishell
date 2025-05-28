/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:00:04 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 15:00:01 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	g_excode_return(int status)
{
	if (WIFEXITED(status))
		g_excode = WEXITSTATUS(status);
	else
		g_excode = 1;
}

void	input_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	t_dir	dir;

	dir.trim = trim_file(right);
	dir.fd = open(dir.trim, O_RDONLY);
	if (dir.fd < 0)
		return (fd_err(&dir.trim), (void) NULL);
	dir.pid = fork();
	if (dir.pid < 0)
		return (fork_err_dir(&dir.trim), (void) NULL);
	if (dir.pid == 0)
		child_input(&dir, ctxt, left, envp);
	close(dir.fd);
	free(dir.trim);
	dir.trim = NULL;
	waitpid(dir.pid, &dir.status, 0);
	g_excode_return (dir.status);
}

void	output_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	t_dir	dir;

	dir.trim = trim_file(right);
	dir.fd = open(dir.trim, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (dir.fd < 0)
		return (fd_err(&dir.trim), (void) NULL);
	dir.pid = fork();
	if (dir.pid < 0)
		return (fork_err_dir(&dir.trim), (void) NULL);
	if (dir.pid == 0)
		child_output(&dir, ctxt, left, envp);
	close(dir.fd);
	free(dir.trim);
	dir.trim = NULL;
	waitpid(dir.pid, &dir.status, 0);
	g_excode_return(dir.status);
}

void	output_append(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	t_dir	dir;

	dir.trim = trim_file(right);
	dir.fd = open(dir.trim, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (dir.fd < 0)
		return (fd_err(&dir.trim), (void) NULL);
	dir.pid = fork();
	if (dir.pid < 0)
		return (fork_err_dir(&dir.trim), (void) NULL);
	if (dir.pid == 0)
		child_output(&dir, ctxt, left, envp);
	close(dir.fd);
	free(dir.trim);
	dir.trim = NULL;
	waitpid(dir.pid, &dir.status, 0);
	g_excode_return (dir.status);
}

void	di_to_dir(t_node *right, t_node *left, char **envp, t_ctxt *ctxt)
{
	input_dir(right, left, envp, ctxt);
	if (unlink(right->data.str) == -1)
		perror("unlink failed");
}
