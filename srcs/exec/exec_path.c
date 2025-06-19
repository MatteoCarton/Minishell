/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:51:37 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/19 23:30:23 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_file_error(const char *path, const char *error_msg)
{
	write(2, "matteoshell: ", 13);
	write(2, path, ft_strlen(path));
	write(2, error_msg, ft_strlen(error_msg));
}

int	check_file_exists(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		print_file_error(path, ": No such file or directory\n");
		g_exitcode = 127;
		return (0);
	}
	return (1);
}

int	check_file_permissions(const char *path)
{
	if (!check_file_exists(path))
		return (0);
	if (!check_is_directory(path))
		return (0);
	if (access(path, X_OK) != 0)
	{
		print_file_error(path, ": Permission denied\n");
		g_exitcode = 126;
		return (0);
	}
	return (1);
}

char	*handle_absolute_path(char *cmd)
{
	char	*path;

	path = ft_strdup(cmd);
	if (!check_file_permissions(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}

char	*get_exec_path(char *cmd, char **env)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (handle_absolute_path(cmd));
	path = find_command_path(cmd, env);
	if (!path)
		return (handle_command_not_found(cmd));
	if (!check_file_permissions(path))
	{
		free(path);
		return (NULL);
	}
	return (path);
}
