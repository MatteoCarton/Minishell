/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alama <alama@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:12:01 by alama             #+#    #+#             */
/*   Updated: 2025/01/13 18:17:12 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

static char	**set_path(char **envp)
{
	int		i;
	int		size;
	char	*tmp;
	char	**test_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	size = ft_strlen(envp[i]);
	tmp = ft_substr(envp[i], 5, size - 5);
	test_path = ft_split(tmp, ':');
	free(tmp);
	tmp = NULL;
	return (test_path);
}

char	*find_path(char **envp, char **cmd)
{
	char	**path;
	char	*c_path;
	char	*tmp;
	int		i;

	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	path = set_path(envp);
	tmp = ft_strjoin("/", cmd[0]);
	if ((tmp[0] == '/' && tmp[1] == '/') || (tmp[0] == '/' && tmp[1] == '.'))
		return (NULL);
	i = 0;
	while (path[i])
	{
		c_path = ft_strjoin(path[i], tmp);
		if (access(c_path, X_OK) == 0)
			return (free(tmp), ft_free_str(path), c_path);
		i++;
		free(c_path);
	}
	free(tmp);
	ft_free_str(path);
	return (NULL);
}
