/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:55:09 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:27:34 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	remove_line(char ***env, int unset)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	len = 0;
	i = 0;
	j = 0;
	while ((*env)[len])
		len++;
	new = malloc(sizeof(char *) * len);
	if (!new)
		return ;
	while (i < len)
	{
		if (i != unset)
		{
			new[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	free_env(*env);
	*env = new;
}

static int	get_line_unset(char **env, char *unset)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(unset);
	while (env[i])
	{
		if (ft_strncmp(env[i], unset, j) == 0 && (env[i][j] == '='
			|| env[i][j] == '\0'))
			return (i);
		i++;
	}
	return (-19);
}

void	unset_env(char **arg, char ***env, char *var_str, int *exit)
{
	int	unset;

	*exit = 0;
	if (arg[1])
	{
		unset = get_line_unset(*env, var_str);
		if (unset == -19)
			return ;
		else
			remove_line(env, unset);
	}
}
