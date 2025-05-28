/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:03:24 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/08 15:44:20 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	*get_var_name(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	return (ft_substr(env_var, 0, i));
}

void	display_env_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	update_or_add_var(char *arg, char ***env, int *env_size)
{
	int	index_env;

	if (var_exist(arg, *env))
	{
		index_env = find_var_index(get_var_name(arg), *env);
		free((*env)[index_env]);
		(*env)[index_env] = ft_strdup(arg);
	}
	else
	{
		(*env)[*env_size] = ft_strdup(arg);
		(*env_size)++;
	}
}

void	ft_export(char **args, char ***env)
{
	int	i;
	int	env_size;

	i = 1;
	env_size = get_2d_array_size(*env);
	if (args[1] == NULL)
	{
		display_env_vars(*env);
		return ;
	}
	while (args[i])
	{
		if (is_valid_var_name(args[i]))
			update_or_add_var(args[i], env, &env_size);
		else
		{
			write(2, "export: not a valid identifier\n", 31);
			g_excode = 1;
		}
		i++;
	}
}
