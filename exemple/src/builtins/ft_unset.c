/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:23:21 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 15:10:49 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	ft_match_env_var(char *env_var, char *arg)
{
	if ((ft_strncmp(env_var, arg, ft_strlen(arg)) == 0
			&& env_var[ft_strlen(arg)] == '\0')
		|| (ft_strncmp(env_var, arg, ft_strlen(arg)) == 0
			&& env_var[ft_strlen(arg)] == '='))
		return (1);
	return (0);
}

static void	ft_shift_env(char **env, int start, size_t *env_size)
{
	int	k;

	free(env[start]);
	k = start;
	while (k < (int)(*env_size - 1))
	{
		env[k] = env[k + 1];
		k++;
	}
	env[k] = NULL;
	(*env_size)--;
}

static void	ft_unset_var(char *arg, char **env, size_t *env_size)
{
	int	i;

	i = 0;
	while (i < (int)(*env_size))
	{
		if (ft_match_env_var(env[i], arg))
		{
			ft_shift_env(env, i, env_size);
			i--;
		}
		i++;
	}
}

void	ft_unset(char **args, char ***env)
{
	size_t	env_size;
	int		j;

	if (!args || !args[1])
		return ;
	env_size = get_2d_array_size(*env);
	j = 1;
	while (args[j])
	{
		ft_unset_var(args[j], *env, &env_size);
		j++;
	}
}
