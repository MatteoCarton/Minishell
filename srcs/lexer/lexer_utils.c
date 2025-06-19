/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:53:26 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 17:08:01 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*add a la liste, si la liste est vide on set le premier
a la tete ensuite on dit on add next ect*/
void	add_token(t_token **head, t_token **actual, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		*actual = new;
	}
	else if (*actual)
	{
		(*actual)->next = new;
		*actual = new;
	}
}

int	check_quotes(char *line)
{
	int		i;
	char	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"'))
		{
			if (!open)
				open = line[i];
			else if (line[i] == open)
				open = 0;
		}
		i++;
	}
	if (open == 0)
		return (1);
	else
		return (0);
}

void	word_token(char *str, t_token **head, t_token **actual, int *i)
{
	char	buff[4096];
	int		j;
	t_token	*new;

	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '|'
		&& str[*i] != '<' && str[*i] != '>')
		process_word_quotes(str, buff, i, &j);
	buff[j] = '\0';
	if (j > 0)
	{
		new = create_token(WORD, buff);
		add_token(head, actual, new);
	}
}

static void	process_quotes(char *str, char *buff, int *i, int *j)
{
	char	q;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		q = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != q && *j < 4095)
			buff[(*j)++] = str[(*i)++];
		if (str[*i] == q)
			(*i)++;
	}
	else if (str[*i] == 32 || str[*i] == '<' || str[*i] == '>'
		|| str[*i] == '|')
		return ;
	else
		buff[(*j)++] = str[(*i)++];
}

void	other_token(char *str, t_token **head, t_token **actual, int *i)
{
	t_token		*new;
	int			begun;
	char		*word;

	begun = *i;
	while (str[*i] && is_valid_word(str[*i]))
		(*i)++;
	word = ft_substr(str, begun, *i - begun);
	if (!word)
		return ;
	new = create_token(WORD, word);
	add_token(head, actual, new);
	free(word);
}
