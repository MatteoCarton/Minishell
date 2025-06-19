/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:20:42 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 10:20:43 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*build_path(char *dir, char *cmd)
{
	char	*full;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full = malloc(dir_len + 1 + cmd_len + 1);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, dir_len + 1);
	ft_strlcat(full, "/", dir_len + 2);
	ft_strlcat(full, cmd, dir_len + 2 + cmd_len);
	return (full);
}

static char	*search_in_path(char **path_array, char *cmd)
{
	char	*test_path;
	int		j;

	j = 0;
	while (path_array[j])
	{
		test_path = build_path(path_array[j], cmd);
		if (test_path && access(test_path, X_OK) == 0)
			return (test_path);
		free(test_path);
		j++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path_var;
	char	**path_array;
	char	*result;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_var = find_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	path_array = ft_split(path_var, ':');
	if (!path_array)
		return (NULL);
	result = search_in_path(path_array, cmd);
	free_tab(path_array);
	return (result);
}
