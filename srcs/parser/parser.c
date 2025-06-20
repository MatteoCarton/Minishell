/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:33:21 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 16:57:02 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_redirection(t_command *cmd, t_token *current)
{
	t_token	*next;

	next = current->next;
	if (!next || next->type != WORD)
		return (0);
	if (!add_redirection(&cmd->redirection, current->type, next->str))
		return (0);
	return (1);
}

static int	parse_pipe(t_command **cmd, t_command *first_cmd, t_token *current)
{
	if (!current->next || current->next->type == PIPE)
	{
		write(2, "matteoshell: syntax error\n", 26);
		g_exitcode = 2;
		free_command(first_cmd);
		return (1);
	}
	*cmd = handle_pipe(*cmd);
	if (!*cmd)
	{
		free_command(first_cmd);
		return (1);
	}
	return (0);
}

static int	parse_redirection(t_command *cmd, t_command *first_cmd,
		t_token **current)
{
	if (!handle_redirection(cmd, *current))
	{
		write(2, "matteoshell: syntax error\n", 26);
		g_exitcode = 2;
		free_command(first_cmd);
		return (1);
	}
	*current = (*current)->next;
	return (0);
}

static int	parse_while(t_command **cmd, t_command **first_cmd,
		t_token **current)
{
	while (*current)
	{
		if ((*current)->type == WORD)
			add_argument(*cmd, (*current)->str);
		else if ((*current)->type == PIPE)
		{
			if (parse_pipe(cmd, *first_cmd, *current))
				return (1);
		}
		else if ((*current)->type == IN || (*current)->type == OUT
			|| (*current)->type == APPEND || (*current)->type == HEREDOC)
		{
			if (parse_redirection(*cmd, *first_cmd, current))
				return (1);
		}
		(*current) = (*current)->next;
	}
	return (0);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*first_cmd;
	t_command	*cmd;
	t_token		*current;

	if (!tokens)
		return (NULL);
	if (tokens->type == PIPE)
		return (write(2, "matteoshell: syntax error\n", 26), NULL);
	first_cmd = init_command();
	cmd = first_cmd;
	current = tokens;
	if (parse_while(&cmd, &first_cmd, &current) == 1)
		return (NULL);
	return (first_cmd);
}
