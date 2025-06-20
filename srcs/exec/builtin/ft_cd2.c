/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:50:44 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 16:30:32 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	update_env_var(char **env, const char *name, const char *value)
{
	size_t	i;
	size_t	len;
	char	*new_var;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			new_var = malloc(len + 1 + ft_strlen(value) + 1);
			if (!new_var)
				return ;
			ft_strlcpy(new_var, name, len + 1);
			new_var[len] = '=';
			ft_strlcpy(new_var + len + 1, value, ft_strlen(value) + 1);
			free(env[i]);
			env[i] = new_var;
			return ;
		}
		i++;
	}
}

char	*update_old_pwd_env(char **env)
{
	int		i;
	char	*old_pwd;

	old_pwd = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			old_pwd = env[i] + 4;
			break ;
		}
		i++;
	}
	if (old_pwd)
		update_env_var(env, "OLDPWD", old_pwd);
	return (old_pwd);
}

int	update_new_pwd_env(char **env)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX))
		update_env_var(env, "PWD", buffer);
	else
	{
		perror("matteoshell: cd (getcwd)");
		return (1);
	}
	return (0);
}
