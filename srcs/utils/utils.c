/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:42:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/05/19 20:13:16 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	handle_whitespace(char *line, int *i, int *start)
{
	while (line[*i] && is_whitespace(line[*i]))
		(*i)++;
	*start = *i;
	return (1);
}

int	is_in_quotes(char *line, int i)
{
	int	j;
	int	in_quotes;

	j = 0;
	in_quotes = 0;
	while (j < i)
	{
		if (line[j] == '\'' || line[j] == '"')
		{
			if (in_quotes == 0)
				in_quotes = line[j];
			else if (in_quotes == line[j])
				in_quotes = 0;
		}
		j++;
	}
	if (in_quotes != 0)
		return (1);
	return (0);
} 