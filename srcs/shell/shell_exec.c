/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:13:08 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 16:17:23 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_command(t_command *cmd, t_shell *m, t_token *lexed)
{
	int	result;

	result = exec(cmd, m);
	free_command(cmd);
	if (result == -19)
	{
		free_token(&lexed);
		return (-19);
	}
	return (1);
}

int	handle_tokens(t_token *lexed, t_shell *m)
{
	t_command	*cmd;
	int			result;

	cmd = parse_tokens(lexed);
	if (!cmd)
	{
		free_command(cmd);
		free_token(&lexed);
		return (1);
	}
	result = handle_command(cmd, m, lexed);
	free_token(&lexed);
	return (result);
}

int	start(char **line, t_shell *m)
{
	t_token	*lexed;

	if (!(**line))
		return (1);
	if (!check_quotes(*line))
		return (0);
	expand_dollar(line, *m);
	lexed = get_token(*line);
	if (!lexed)
		return (0);
	return (handle_tokens(lexed, m));
}
