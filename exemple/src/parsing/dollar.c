/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:15 by alama             #+#    #+#             */
/*   Updated: 2025/01/19 19:18:42 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	handle_quotes(t_quotes *test, char *str)
{
	if (str[test->i] == '\'' && !test->in_double_quotes)
	{
		test->in_single_quotes = !test->in_single_quotes;
		test->result = add_char_to_result(test->result, str[test->i]);
		return (1);
	}
	else if (str[test->i] == '"' && !test->in_single_quotes)
	{
		test->in_double_quotes = !test->in_double_quotes;
		test->result = add_char_to_result(test->result, str[test->i]);
		return (1);
	}
	return (0);
}

int	init_quotes(t_quotes *test)
{
	test->result = ft_strdup("");
	if (!test->result)
		return (0);
	test->in_single_quotes = 0;
	test->in_double_quotes = 0;
	test->i = 0;
	return (1);
}

int	result_char(t_quotes *test, char *str)
{
	test->result = add_char_to_result(test->result, str[test->i]);
	if (!test->result)
		return (0);
	return (1);
}

void	handle_handle(t_quotes *test)
{
	test->result = handle_exit_code(&test->result);
	test->i++;
}

char	*replace_dollar_str(char *str, char **env)
{
	t_quotes	test;

	if (init_quotes(&test) == 0)
		return (NULL);
	while (str[test.i])
	{
		if (handle_quotes(&test, str) == 1)
			;
		else if (str[test.i] == '$' && !test.in_single_quotes)
		{
			if (str[test.i + 1] == '?')
				handle_handle(&test);
			else
			{
				test.result = handle_dollar(&test.result, str, &test.i, env);
				if (!test.result)
					return (NULL);
				continue ;
			}
		}
		else if (result_char(&test, str) == 0)
			return (NULL);
		test.i++;
	}
	return (test.result);
}
