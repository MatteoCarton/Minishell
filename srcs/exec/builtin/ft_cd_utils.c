/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:00:00 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 18:34:11 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*ft_strjoin_path(char const *str1, char const *str2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, str1, len1 + 1);
	if (len1 > 0 && str[len1 - 1] != '/')
	{
		str[len1] = '/';
		len1++;
	}
	ft_strlcpy(str + len1, str2, len2 + 1);
	return (str);
}

char	*normalize_path(const char *path)
{
	char	**components;
	t_list	*path_list;
	char	*new_path;

	if (!path)
		return (NULL);
	components = ft_split(path, '/');
	if (!components)
		return (NULL);
	path_list = NULL;
	fill_path_list(&path_list, components);
	free_components(components);
	new_path = ft_lst_to_path(path_list);
	ft_lstclear(&path_list, free);
	return (new_path);
}

void	update_pwd_vars(t_shell *shell, const char *new_pwd)
{
	char	*pwd_val;

	pwd_val = find_env_value(shell->env, "PWD");
	if (pwd_val)
		update_env_var(shell->env, "OLDPWD", pwd_val);
	update_env_var(shell->env, "PWD", new_pwd);
}
