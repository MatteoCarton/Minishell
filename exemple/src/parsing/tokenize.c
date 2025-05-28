/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:20:21 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 14:19:33 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_is_lexeme(char c)
{
	if (c != ' ' && c != '|' && c != '<' && c != '>' && c != '\"' && c != '\''
		&& c != '(' && c != ')' && c != ';' && c != '\\')
		return (0);
	return (1);
}

void	ft_add_token(t_token **token, t_token_type type, char *lexeme)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_free_token(token);
		exit(write(2, "malloc from tokens fails\n", 25));
	}
	new_token->type = type;
	new_token->lexeme = lexeme;
	new_token->next = NULL;
	if (!token || !*token)
	{
		new_token->prev = NULL;
		*token = new_token;
		return ;
	}
	last = *token;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_token;
	new_token->prev = last;
}

int	ft_str_to_lexeme(int i, char *str, t_token **token_list, t_token_type type)
{
	int		start;
	char	*lexeme;
	int		found;

	if (type != CHAR_TOKEN)
		i++;
	start = i;
	while (str[i] != '\0' && str[i] != '\n' && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && str[i] != ')' && str[i] != '\"' && str[i] != '\''
		&& str[i] != '\\' && str[i] != ';')
	{
		if (type == CHAR_TOKEN && str[i] == ' ')
			break ;
		else
			i++;
	}
	found = 0;
	if (ft_is_lexeme(str[i]) == 1)
		found = 1;
	lexeme = ft_strndup(&str[start], i - start);
	ft_add_token(token_list, type, lexeme);
	if (found == 1)
		i--;
	return (i);
}

int	which_token(int *i, char *str, t_token **token_list)
{
	if (handle_space_token(i, str, token_list) == -1)
		return (-1);
	if (handle_pipe_token(i, str, token_list) == -1)
		return (-1);
	if (str[*i] == '(' || str[*i] == ')')
		return (handle_parentheses_token(str[*i]));
	if (handle_quotes_token(i, str, token_list) == -1)
		return (-1);
	if (handle_redirection_token(i, str, token_list) == -1)
		return (-1);
	if (str[*i] == '\\' || str[*i] == ';')
		return (handle_invalid_token(str[*i]));
	return (*i);
}

t_token	*tokenize(char *str)
{
	t_token	*token_list;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
		token_list = inside_tokenize(&i, str, token_list);
	if (token_list)
		ft_add_token(&token_list, END_TOKEN, NULL);
	return (token_list);
}
