/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:09 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 14:48:14 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_count_quotes(const char *str, int *dq_count, int *sq_count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			(*dq_count)++;
		if (str[i] == '\'')
			(*sq_count)++;
		i++;
	}
}

int	ft_should_skip_quote(char c, int dq_count, int sq_count)
{
	if (c == '"' && dq_count % 2 == 0)
		return (1);
	if (c == '\'' && sq_count % 2 == 0)
		return (1);
	return (0);
}

char	*ft_remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	int		dq_count;
	int		sq_count;

	dq_count = 0;
	sq_count = 0;
	ft_count_quotes(str, &dq_count, &sq_count);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_should_skip_quote(str[i], dq_count, sq_count))
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	ft_numbers_of_singlequotes(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nbr++;
		i++;
	}
	return (nbr);
}

int	ft_is_valid_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
