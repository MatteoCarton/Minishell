/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:12 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 14:51:59 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	verify_equals(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(char **args, char **env)
{
	int	i;

	i = 0;
	(void)args;
	while (env[i] && verify_equals(env[i]))
	{
		printf("%s\n", env[i]);
		i++;
	}
}
