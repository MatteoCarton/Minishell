/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:25:14 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/06 10:16:15 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*remove_backslashes(const char *str)
{
	char	*result;
	char	*write_ptr;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	write_ptr = result;
	while (*str)
	{
		if (*str == '\\' && *(str + 1))
		{
			str++;
		}
		*write_ptr++ = *str++;
	}
	*write_ptr = '\0';
	return (result);
}

void	clean_str_nodes(t_node *node)
{
	char	*cleaned_str;

	if (!node)
		return ;
	if (node->type == STR_NODE)
	{
		cleaned_str = remove_backslashes(node->data.str);
		free(node->data.str);
		node->data.str = cleaned_str;
	}
	else if (node->type == PAIR_NODE)
	{
		clean_str_nodes(node->data.pair.left);
		clean_str_nodes(node->data.pair.right);
	}
}
