/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:39:34 by mcarton           #+#    #+#             */
/*   Updated: 2025/05/19 20:17:10 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	copy_command(t_cmd *cmd, char *line)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	handle_whitespace(line, &i, &start);
	while (line[i] && !is_whitespace(line[i]))
		i++;
	cmd->cmd = malloc(sizeof(char) * (i - start + 1));
	if (!cmd->cmd)
		return (0);
	j = 0;
	while (start < i)
	{
		cmd->cmd[j] = line[start];
		j++;
		start++;
	}
	cmd->cmd[j] = '\0';
	return (1);
}