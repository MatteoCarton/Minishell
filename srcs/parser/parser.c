/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:33:21 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 01:32:23 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_argument(t_command *cmd, t_token *current)
{
	add_argument(cmd, current->str);
}

t_command	*handle_pipe(t_command *cmd)
{
	cmd->next = init_command();
	if (!cmd->next)
		return (NULL);
	cmd = cmd->next;
	return (cmd);
}

int	handle_redirection(t_command *cmd, t_token *current)
{
	t_token	*next;

	next = current->next;
	if (!next || next->type != WORD)
		return (0);
	if (!add_redirection(&cmd->redirection, current->type, next->str))
		return (0);
	return (1);
}

int	parse_while(t_command **cmd, t_command **first_cmd,
		t_token **current)
{
	while ((*current))
	{
		if ((*current)->type == WORD)
			handle_argument((*cmd), (*current));
		else if ((*current)->type == PIPE)
		{
			if (!(*current)->next || (*current)->next->type == PIPE)
				return (write(2, "matteoshell: syntax error\n", 26),
					free_command((*first_cmd)), 1);
			(*cmd) = handle_pipe((*cmd));
			if (!(*cmd))
				return (free_command((*first_cmd)), 1);
		}
		else if ((*current)->type == IN || (*current)->type == OUT
			|| (*current)->type == APPEND || (*current)->type == HEREDOC)
		{
			if (!handle_redirection((*cmd), (*current)))
				return (free_command((*first_cmd)), 1);
			(*current) = (*current)->next;
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
