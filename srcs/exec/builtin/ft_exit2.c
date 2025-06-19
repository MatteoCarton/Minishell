/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:52:42 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 11:00:05 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	handle_sign(const char *str, int *i)
{
	bool	plus_sign;

	plus_sign = true;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			plus_sign = false;
		(*i)++;
	}
	return (plus_sign);
}

bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (arg[i] == '\0')
		return (false);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi_with_overflow(const char *str, int *error)
{
	int			i;
	bool		plus_sign;
	long long	result;

	i = 0;
	result = 0;
	plus_sign = handle_sign(str, &i);
	*error = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (overflow_or_not(result, str[i] - '0', plus_sign, str))
		{
			*error = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (plus_sign)
		return (result);
	return (-result);
}
