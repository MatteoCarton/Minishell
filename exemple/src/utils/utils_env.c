/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:00:16 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 14:20:39 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

char	**copy_env(char **env)
{
	size_t	i;
	size_t	env_size;
	char	**new_env;

	i = 0;
	env_size = get_2d_array_size(env);
	new_env = malloc(sizeof(char *) * (100));
	if (!new_env)
		return (NULL);
	while (i < env_size)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_free_env(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
