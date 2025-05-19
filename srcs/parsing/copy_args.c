/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:40:38 by mcarton           #+#    #+#             */
/*   Updated: 2025/05/19 20:48:02 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_arguments(char *line, int cmd_end)
{
	int	argc;
	int	i;
	int	start;

	argc = 0;
	i = cmd_end;
	handle_whitespace(line, &i, &start);
	while (line[i])
	{
		if (is_whitespace(line[i]))
		{
			if (!is_in_quotes(line, i))
				argc++;
			handle_whitespace(line, &i, &start);
		}
		else
			i++;
	}
	if (i > start)
		argc++;
	return (argc);
}

int	copy_single_arg(char **args, int argc, char *line, int *pos)
{
	int	j;

	args[argc] = malloc(sizeof(char) * (pos[1] - pos[0] + 1));
	if (!args[argc])
		return (0);
	j = 0;
	while (pos[0] < pos[1])
	{
		args[argc][j] = line[pos[0]];
		j++;
		pos[0]++;
	}
	args[argc][j] = '\0';
	return (1);
}

int	handle_arg(char **args, int *argc, char *line, int *pos)
{
	if (!is_in_quotes(line, pos[1]))
	{
		if (!copy_single_arg(args, *argc, line, pos))
			return (0);
		(*argc)++;
		handle_whitespace(line, &pos[1], &pos[0]);
	}
	else
		pos[1]++;
	return (1);
}

int	process_args(char **args, char *line, int *argc, int cmd_end)
{
    /*  pos[0] = position de début d'un argument (start)
        pos[1] = position actuelle dans la ligne (i)    */
	int	pos[2];

    pos[0] = cmd_end;
	pos[1] = cmd_end;
	*argc = 0;
	handle_whitespace(line, &pos[1], &pos[0]);
	while (line[pos[1]])
	{
		if (is_whitespace(line[pos[1]]) && !is_in_quotes(line, pos[1]))
		{
			if (!handle_arg(args, argc, line, pos))
				return (0);
		}
		else
			pos[1]++;
	}
	if (pos[1] > pos[0])
	{
		if (!copy_single_arg(args, *argc, line, pos))
			return (0);
		(*argc)++;
	}
	return (1);
}

int	copy_arguments(t_cmd *cmd, char *line, int cmd_end)
{
	int		argc;
	char	**args;

	argc = count_arguments(line, cmd_end);
	args = malloc(sizeof(char *) * (argc + 1));
	if (!args)
		return (0);
	args[argc] = NULL;
	if (!process_args(args, line, &argc, cmd_end))
		return (0);
	cmd->args = args;
	cmd->argc = argc;
	return (1);
}
