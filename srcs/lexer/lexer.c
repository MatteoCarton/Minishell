/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:00:00 by minishell42       #+#    #+#             */
/*   Updated: 2025/06/19 11:10:04 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*dans la fonction handle quotes juste gerer les char*/
int	is_valid_word(char c)
{
	return (ft_isalnum(c) || c == '"' || c == '\'' || ft_strchr(EXTRA_CHAR, c));
}

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

void	check_token(char *line, t_token **head, t_token **actual, int *i)
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

/*on cree token malloc size de la struct puis on dup str ,
	def le type et set le next a NUll
puis on return*/
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
