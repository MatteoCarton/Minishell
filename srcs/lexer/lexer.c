/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:27:38 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:01:01 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_word_quotes(char *str, char *buff, int *i, int *j)
{
	char	q;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		q = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != q && *j < 4095)
			buff[(*j)++] = str[(*i)++];
		if (str[*i] == q)
			(*i)++;
	}
	else
		buff[(*j)++] = str[(*i)++];
}

static void	check_token(char *line, t_token **head, t_token **actual, int *i)
{
	while (line[*i])
	{
		if ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32)
			(*i)++;
		else if (line[*i] == '|')
			pipe_token(line, head, actual, i);
		else if (line[*i] == '>' || line[*i] == '<')
			in_out_token(line, head, actual, i);
		else
			word_token(line, head, actual, i);
	}
}

t_token	*create_token(t_token_type type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!new->str)
		return (free(new), NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*get_token(char *line)
{
	int		i;
	t_token	*head;
	t_token	*actual;

	i = 0;
	head = NULL;
	actual = NULL;
	check_token(line, &head, &actual, &i);
	return (head);
}
