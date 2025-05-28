/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 15:05:52 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

size_t	get_2d_array_size(char **array)
{
	size_t	size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}

int	is_valid_var_name(char *var)
{
	int	i;
	int	equals_found;

	i = 0;
	equals_found = 0;
	if (!var || var[0] == '=')
		return (0);
	while (var[i] != '\0')
	{
		if (var[i] == '=')
		{
			if (equals_found)
				return (0);
			equals_found = 1;
			i++;
			break ;
		}
		if (!((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A'
					&& var[i] <= 'Z') || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	len_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	var_exist(char *arg, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = len_arg(arg);
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	find_var_index(char *arg, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(arg);
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
