/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_close_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:29:37 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 16:05:38 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_not_close(char c)
{
	write(2, "syntax error near unexpected token `", 36);
	write(2, &c, 1);
	write(2, "\'\n", 2);
}

int	ft_quote_to_lexeme(int i, char *str, t_token **tok, t_token_type type)
{
	int		start;
	char	*lexeme;

	i++;
	start = i;
	if (type == SINGLE_QUOTE)
	{
		while (str[i] && (str[i] != '\'' && str[i - 1] != '\\'))
			i++;
	}
	else if (type == DOUBLE_QUOTE)
	{
		while (str[i] && (str[i] != '\"' && str[i - 1] != '\\'))
			i++;
	}
	if (str[i] == '\0')
		return (-1);
	lexeme = ft_strndup(&str[start - 1], i - start + 2);
	ft_add_token(tok, type, lexeme);
	return (i);
}

int	d_and_s_token(int *i, char *str, t_token **token_list)
{
	if (str[*i] == '\'')
	{
		*i = ft_quote_to_lexeme(*i, str, token_list, SINGLE_QUOTE);
		if (*i == -1)
			ft_not_close('\'');
	}
	else
	{
		*i = ft_quote_to_lexeme(*i, str, token_list, DOUBLE_QUOTE);
		if (*i == -1)
			ft_not_close('\"');
	}
	return (*i);
}
