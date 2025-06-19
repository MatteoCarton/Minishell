/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:07:27 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 17:18:11 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env_value(char **env, char *var)
{
	int	i;
	int	len;

	if (!env || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_var_name(char *str)
{
	int		i;
	int		len;
	int		j;
	char	*name;

	i = 1;
	len = 0;
	j = 0;
	if (!str || str[0] != '$')
		return (NULL);
	while (str[i + len] && (isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	while (j < len)
	{
		name[j] = str[i + j];
		j++;
	}
	name[len] = '\0';
	return (name);
}

char	*handle_env_var(char **str, t_shell g_env, int *i)
{
	char	*var_name;
	char	*env_value;
	char	*to_add;

	var_name = get_var_name(&(*str)[*i]);
	if (var_name)
	{
		env_value = find_env_value(g_env.env, var_name);
		if (!env_value)
			to_add = strdup("");
		else
			to_add = strdup(env_value);
		*i += strlen(var_name);
		free(var_name);
	}
	else
		to_add = strdup("$");
	return (to_add);
}

char	*get_replacement_value(char **str, t_shell g_env, int *i)
{
	char	*to_add;

	if (!(*str)[*i + 1] || (*str)[*i + 1] == ' ')
		to_add = strdup("$");
	else if ((*str)[*i + 1] == '?')
	{
		to_add = ft_itoa(g_exitcode);
		(*i)++;
	}
	else
		to_add = handle_env_var(str, g_env, i);
	return (to_add);
}

void	replace_dollar(char **str, char **new_str, t_shell g_env, int *i)
{
	char	*to_add;

	to_add = get_replacement_value(str, g_env, i);
	*new_str = join_str(*new_str, to_add);
	free(to_add);
}
