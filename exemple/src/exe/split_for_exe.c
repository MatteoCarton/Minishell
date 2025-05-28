/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:26:50 by alama             #+#    #+#             */
/*   Updated: 2025/01/16 17:34:19 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	add_space_split(char **data)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while (data[j] != NULL)
	{
		str = data[j];
		i = 0;
		while (str[i])
		{
			if (str[i] == -32)
				str[i] *= -1;
			i++;
		}
		j++;
	}
}

static void	compare_to_space(t_node *node, int *i)
{
	char	*tmp;

	tmp = node->data.str;
	if (tmp[*i] == ' ')
		tmp[*i] = tmp[*i] * -1;
	(*i)++;
}

void	split_for_exe(t_node *node)
{
	int		i;
	char	*str;

	i = 0;
	str = node->data.str;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i + 1] && str[i + 1] != '\''
				&& str[i] != '\\')
				compare_to_space(node, &i);
		}
		if (str[i] == '\"')
		{
			while (str[i + 1] && str[i + 1] != '\"' && str[i] != '\\')
				compare_to_space(node, &i);
		}
		i++;
	}
}

void	remove_quote(char **data)
{
	int		i;
	char	*str;

	i = 0;
	while (data[i] != NULL)
	{
		if (data[i][0] == '\'')
		{
			str = ft_strtrim(data[i], "\'");
			free(data[i]);
			data[i] = str;
		}
		if (data[i][0] == '\"')
		{
			str = ft_strtrim(data[i], "\"");
			free(data[i]);
			data[i] = str;
		}
		i++;
	}
}
