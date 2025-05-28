/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:21:22 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/19 15:15:13 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	count_digits(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_digits(char *res, int n, int len)
{
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	while (n)
	{
		res[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*itoa_exit_code(int n)
{
	char	*res;
	int		len;

	len = count_digits(n);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	fill_digits(res, n, len);
	return (res);
}

char	*handle_simple_dollar(char **result)
{
	char	substr[2];
	char	*temp;

	substr[0] = '$';
	substr[1] = '\0';
	temp = *result;
	*result = ft_strjoin(temp, substr);
	free(temp);
	temp = NULL;
	return (*result);
}

char	*handle_exit_code(char **result)
{
	char	*temp;
	char	*exit_code_str;

	exit_code_str = itoa_exit_code(g_excode);
	if (!exit_code_str)
		return (NULL);
	temp = *result;
	*result = ft_strjoin(temp, exit_code_str);
	free(temp);
	temp = NULL;
	free(exit_code_str);
	exit_code_str = NULL;
	return (*result);
}
