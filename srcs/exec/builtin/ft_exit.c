/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:53:46 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 10:54:06 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	overflow_positive(long long result, int digit, const char *str)
{
	if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
			&& digit > LLONG_MAX % 10))
	{
		write(2, "minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		return (1);
	}
	return (0);
}

int	overflow_negative(long long result, int digit, const char *str)
{
	if ((unsigned long long)result > (unsigned long long)LLONG_MAX / 10
		|| ((unsigned long long)result == (unsigned long long)LLONG_MAX / 10
			&& (unsigned long long)digit > ((unsigned long long)LLONG_MAX % 10
				+ 1)))
	{
		write(2, "minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		return (1);
	}
	return (0);
}

int	overflow_or_not(long long result, int digit, bool plus_sign,
		const char *str)
{
	if (plus_sign)
		return (overflow_positive(result, digit, str));
	else
		return (overflow_negative(result, digit, str));
}

int	handle_exit_errors(char **args)
{
	if (!args || number_of_args(args) == 1)
		return (-19);
	if (!is_numeric(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		g_exitcode = 2;
		return (-19);
	}
	if (number_of_args(args) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_exitcode = 1;
		return (0);
	}
	return (42);
}

int	ft_exit(char **args)
{
	int	code;
	int	error;
	int	err;

	printf("exit\n");
	err = handle_exit_errors(args);
	if (err != 42)
		return (err);
	code = ft_atoi_with_overflow(args[1], &error);
	if (error)
	{
		g_exitcode = 2;
		return (-19);
	}
	g_exitcode = (unsigned char)code;
	return (-19);
}
