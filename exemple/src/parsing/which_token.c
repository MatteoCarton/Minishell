/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:22:05 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 13:27:38 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	handle_space_token(int *i, char *str, t_token **token_list)
{
	char	*set_malloc;

	if (str[*i + 1] && str[*i] == ' ' && str[*i + 1] != ' ')
	{
		set_malloc = ft_strdup(" ");
		if (!set_malloc)
			return (-1);
		ft_add_token(token_list, SPACE_TOKEN, set_malloc);
	}
	return (0);
}

int	handle_pipe_token(int *i, char *str, t_token **token_list)
{
	char	*set_malloc;

	if (str[*i] == '|')
	{
		set_malloc = ft_strdup("|");
		if (!set_malloc)
			return (-1);
		ft_add_token(token_list, PIPE, set_malloc);
	}
	return (0);
}

int	handle_parentheses_token(int c)
{
	ft_not_close(c);
	return (-1);
}

int	handle_quotes_token(int *i, char *str, t_token **token_list)
{
	if ((str[*i] == '\'' || str[*i] == '\"') && d_and_s_token(i, str,
			token_list) == -1)
		return (-1);
	return (0);
}

int	handle_redirection_token(int *i, char *str, t_token **token_list)
{
	char	*set_malloc;

	if (str[*i] == '>' && str[*i + 1] != '>')
	{
		set_malloc = ft_strdup(">");
		if (!set_malloc)
			return (-1);
		ft_add_token(token_list, O_DIR, set_malloc);
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		set_malloc = ft_strdup(">>");
		if (!set_malloc)
			return (-1);
		ft_add_token(token_list, OA_DIR, set_malloc);
		(*i)++;
	}
	return (0);
}
