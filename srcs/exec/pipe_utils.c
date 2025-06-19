/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:33:44 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 10:45:54 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipes(t_command *cmd)
{
	int			i;
	t_command	*current;

	i = 0;
	current = cmd;
	while (current && current->next)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	setup_pipe_redirections(int *pipes, int index, int n_pipes)
{
	int	i;

	i = 0;
	setup_child_signals();
	if (index > 0)
		dup2(pipes[(index - 1) * 2], STDIN_FILENO);
	if (index < n_pipes)
		dup2(pipes[index * 2 + 1], STDOUT_FILENO);
	while (i < n_pipes * 2)
	{
		close(pipes[i]);
		i++;
	}
}

int	alloc_pipe_array(int **pipes, int n_pipes)
{
	*pipes = malloc(sizeof(int) * n_pipes * 2);
	if (!*pipes)
	{
		perror("minishell: malloc");
		g_exitcode = 1;
		return (1);
	}
	return (0);
}

int	create_pipes(int *pipes, int n_pipes)
{
	int	i;

	i = 0;
	while (i < n_pipes)
	{
		if (pipe(&pipes[i * 2]) == -1)
		{
			perror("minishell: pipe");
			g_exitcode = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
