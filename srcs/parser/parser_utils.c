/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:29:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 16:39:28 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_redirection	*add_redirection(t_redirection **redirection_list,
		t_token_type type, char *filename)
{
	t_redirection	*new;
	t_redirection	*tmp;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = type;
	new->filename = ft_strdup(filename);
	new->heredoc_fd = -1;
	new->next = NULL;
	if (!*redirection_list)
		*redirection_list = new;
	else
	{
		tmp = *redirection_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirection = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	arg_while(t_command **cmd, char **arg, char ***new_args)
{
	int	i;

	i = 0;
	while ((*cmd)->args && (*cmd)->args[i])
	{
		(*new_args)[i] = ft_strdup((*cmd)->args[i]);
		if (!(*new_args)[i])
		{
			while (--i >= 0)
				free((*new_args)[i]);
			free(*new_args);
			free_command(*cmd);
			return ;
		}
		i++;
	}
	(*new_args)[i] = ft_strdup(*arg);
	if (!(*new_args)[i])
	{
		while (--i >= 0)
			free(*new_args[i]);
		free(*new_args);
		free_command(*cmd);
		return ;
	}
}

void	add_argument(t_command *cmd, char *arg)
{
	int		i;
	char	**new_args;
	int		j;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = ft_calloc(sizeof(char *), i + 2);
	if (!new_args)
	{
		free_command(cmd);
		return ;
	}
	arg_while(&cmd, &arg, &new_args);
	j = 0;
	if (cmd->args)
	{
		while (cmd->args[j])
		{
			free(cmd->args[j]);
			j++;
		}
		free(cmd->args);
	}
	cmd->args = new_args;
}
