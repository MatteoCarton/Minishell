/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:26:15 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/19 19:18:51 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*get_env_value(char *var, char **env)
{
	int		i;
	size_t	var_len;

	if (!var || !env)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, var_len) && env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (" ");
}

char	*add_char_to_result(char *result, char c)
{
	char	substr[2];
	char	*temp;

	substr[0] = c;
	substr[1] = '\0';
	temp = result;
	result = ft_strjoin(temp, substr);
	free(temp);
	temp = NULL;
	return (result);
}

void	replace_dollar(t_node *node, char **env)
{
	char	*new_str;

	if (!node || !node->data.str)
		return ;
	new_str = replace_dollar_str(node->data.str, env);
	free(node->data.str);
	node->data.str = new_str;
}

void	add_dollar(t_node *node, char **env)
{
	if (!node)
		return ;
	if (node->type == STR_NODE)
		replace_dollar(node, env);
	else
	{
		if (node->data.pair.left)
			add_dollar(node->data.pair.left, env);
		if (node->data.pair.right)
			add_dollar(node->data.pair.right, env);
	}
}

char	*handle_dollar(char **result, char *str, int *i, char **env)
{
	char	var_name[256];
	char	*var_value;
	char	*temp;
	int		j;

	(*i)++;
	if (str[*i] == '\0' || (str[*i] != '?' && !(ft_isalnum(str[*i])
				|| str[*i] == '_')))
		return (handle_simple_dollar(result));
	if (str[*i] == '?')
		return (handle_exit_code(result));
	j = 0;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	var_value = get_env_value(var_name, env);
	if (!var_value)
		var_value = "";
	temp = *result;
	*result = ft_strjoin(temp, var_value);
	free(temp);
	return (*result);
}
