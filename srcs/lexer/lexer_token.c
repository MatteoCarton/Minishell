/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:53:13 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 16:58:22 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_token(char *line, t_token **head, t_token **actual, int *i)
{
	t_token	*new;

	if ((line[*i]) == '|')
	{
		new = create_token(PIPE, "|");
		add_token(head, actual, new);
		(*i)++;
	}
}

static t_token	*handle_redirect_in(char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			(*i) += 2;
			return (create_token(HEREDOC, "<<"));
		}
		else
		{
			(*i)++;
			return (create_token(IN, "<"));
		}
	}
	return (NULL);
}

static t_token	*handle_redirect_out(char *str, int *i)
{
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			(*i) += 2;
			return (create_token(APPEND, ">>"));
		}
		else
		{
			(*i)++;
			return (create_token(OUT, ">"));
		}
	}
	return (NULL);
}

void	in_out_token(char *str, t_token **head, t_token **actual, int *i)
{
	t_token	*new;

	new = handle_redirect_in(str, i);
	if (!new)
		new = handle_redirect_out(str, i);
	if (new)
		add_token(head, actual, new);
}

void	quotes_token(char *str, t_token **head, t_token **actual, int *i)
{
	t_token		*new;
	char		buff[4096];
	int			j;

	j = 0;
	while (str[*i])
		process_quotes(str, buff, i, &j);
	buff[j] = '\0';
	new = create_token(WORD, buff);
	add_token(head, actual, new);
}
