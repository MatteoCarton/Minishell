/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:54:49 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:25:57 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	add_env_var(char ***env, char *str)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	if (!check_line(env, str))
		return ;
	while ((*env)[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return ;
	while (j < i)
	{
		new[j] = ft_strdup((*env)[j]);
		j++;
	}
	new[j] = ft_strdup(str);
	new[j + 1] = NULL;
	free_env(*env);
	*env = new;
}

static void	fill_export_output(char ***env, char **output, int i)
{
	int		j;
	char	*quoted;

	j = 0;
	while (j < i)
	{
		quoted = get_quoted((*env)[j]);
		if (!quoted)
			output[j] = NULL;
		else
		{
			output[j] = ft_strjoin("declare -x ", quoted);
			free(quoted);
		}
		j++;
	}
	output[j] = NULL;
}

static void	all_export(char ***env)
{
	int		i;
	char	**output;

	i = 0;
	while ((*env)[i])
		i++;
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return ;
	fill_export_output(env, output, i);
	show_env(output);
	free(output);
}

static void	export_with_args(char **arg, char ***env, int *exit)
{
	int	check;
	int	i;
	int	local_exit;

	local_exit = 0;
	i = 1;
	while (arg[i])
	{
		check = valid_env(arg[i]);
		if (!check)
		{
			local_exit = 1;
			write(2, "matteoshell: export: '", 22);
			write(2, arg[i], ft_strlen(arg[i]));
			write(2, "' : not a valid identifier\n", 27);
		}
		else if (arg[i])
		{
			add_env_var(env, arg[i]);
		}
		i++;
	}
	*exit = local_exit;
}

void	export_env(char **arg, char ***env, int *exit)
{
	if (arg[1])
	{
		export_with_args(arg, env, exit);
	}
	else
	{
		all_export(env);
		return ;
	}
}
