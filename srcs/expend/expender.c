/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:02:43 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:05:24 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	joignable(char **str, char **new_str, t_shell g_env, int *i)
{
	if ((*str)[*i] != '$')
		return (0);
	if ((*str)[*i + 1])
	{
		replace_dollar(str, new_str, g_env, i);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	process_char(char **str, char **new_str, t_shell g_env, int *i)
{
	char	*tmp;

	if (!joignable(str, new_str, g_env, i))
	{
		tmp = join_char(*new_str, (*str)[*i]);
		if (!tmp)
		{
			free(*new_str);
			*str = NULL;
			return (0);
		}
		free(*new_str);
		*new_str = tmp;
		(*i)++;
	}
	return (1);
}

static int	add_single_quote_char(char **str, char **new_str, int *i)
{
	char	*tmp;

	tmp = join_char(*new_str, (*str)[*i]);
	if (!tmp)
	{
		free(*new_str);
		*str = NULL;
		return (0);
	}
	free(*new_str);
	*new_str = tmp;
	(*i)++;
	return (1);
}

static int	expand_dollar_loop(char **str, char **new_str, t_shell g_env)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while ((*str)[i])
	{
		update_quotes_state((*str)[i], &in_single, &in_double);
		if (!in_single)
		{
			if (!process_char(str, new_str, g_env, &i))
				return (0);
		}
		else
		{
			if (!add_single_quote_char(str, new_str, &i))
				return (0);
		}
	}
	return (1);
}

void	expand_dollar(char **str, t_shell g_env)
{
	char	*new_str;

	if (!str || !*str)
		return ;
	new_str = strdup("");
	if (!new_str)
	{
		*str = NULL;
		return ;
	}
	if (!expand_dollar_loop(str, &new_str, g_env))
		return ;
	*str = new_str;
}
