/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:50:32 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 18:35:30 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	update_env_var(char **env, const char *name, const char *value)
{
	size_t	i;
	size_t	len;
	char	*new_var;

	if (!value)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			new_var = malloc(len + 1 + ft_strlen(value) + 1);
			if (!new_var)
				return ;
			ft_strlcpy(new_var, name, len + 1);
			new_var[len] = '=';
			ft_strlcpy(new_var + len + 1, value, ft_strlen(value) + 1);
			env[i] = new_var;
			return ;
		}
		i++;
	}
}

static char	*get_logical_path(char *path, t_shell *shell)
{
	char	*current_pwd;

	current_pwd = find_env_value(shell->env, "PWD");
	if (!current_pwd)
		current_pwd = "";
	if (path[0] == '/')
		return (ft_strdup(path));
	return (ft_strjoin_path(current_pwd, path));
}

static void	execute_cd(char *new_pwd, t_shell *shell)
{
	if (chdir(new_pwd) == -1)
	{
		perror("matteoshell: cd");
		g_exitcode = 1;
	}
	else
	{
		update_pwd_vars(shell, new_pwd);
		g_exitcode = 0;
	}
	free(new_pwd);
}

static void	change_directory(char *path, t_shell *shell)
{
	char	*logical_path;
	char	*new_pwd;

	logical_path = get_logical_path(path, shell);
	if (!logical_path)
		return ;
	new_pwd = normalize_path(logical_path);
	free(logical_path);
	if (!new_pwd)
		return ;
	execute_cd(new_pwd, shell);
}

void	ft_cd(char **args, t_shell *shell)
{
	char	*home_path;

	if (number_of_args(args) > 2)
	{
		write(2, "matteoshell: cd: too many arguments\n", 36);
		g_exitcode = 1;
		return ;
	}
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		home_path = find_env_value(shell->env, "HOME");
		if (!home_path)
		{
			write(2, "matteoshell: cd: HOME not set\n", 30);
			g_exitcode = 1;
			return ;
		}
		change_directory(home_path, shell);
	}
	else
		change_directory(args[1], shell);
}
