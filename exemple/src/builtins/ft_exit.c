/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:19:12 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/16 15:03:17 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static char	ft_set_sign(char **str)
{
	char	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int	ft_handle_overflow(long int result, long int tmp, char *str)
{
	if (result < tmp)
	{
		write(2, "minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		return (2);
	}
	return (1);
}

int	ft_atoi2(char *str)
{
	char		sign;
	long int	result;
	long int	tmp;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = ft_set_sign(&str);
	while ((*str >= '0' && *str <= '9') || *str == '"')
	{
		if (*str == '"')
		{
			str++;
			continue ;
		}
		tmp = result;
		result = result * 10 + (*str - '0');
		if (ft_handle_overflow(result, tmp, str) == 2)
			return (2);
		str++;
	}
	return (result * sign);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	write(1, "exit\n", 5);
	if (!args || args[1] == NULL)
		return ;
	if (args[2] != NULL)
	{
		write(2, "minishell: exit: ", 17);
		write(2, "too many arguments\n", 19);
		g_excode = 1;
		return ;
	}
	if (!is_numeric(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		g_excode = 2;
	}
	else
		g_excode = ft_atoi2(args[1]);
}
