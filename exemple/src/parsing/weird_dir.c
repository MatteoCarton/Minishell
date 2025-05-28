/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:03:43 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 15:04:06 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static t_node	*find_next_str_node(t_node *node)
{
	while (node->type != STR_NODE)
		node = node->data.pair.left;
	return (node);
}

static void	merge_with_space(t_node *l, char *to_add)
{
	char	*space;
	char	*tmp;

	space = ft_strjoin(l->data.str, " ");
	tmp = ft_strjoin(space, to_add);
	free(space);
	free(l->data.str);
	l->data.str = tmp;
}

static void	process_split(t_node *left, char **str)
{
	t_node	*l;
	int		i;

	l = left;
	i = 1;
	while (str[i] != NULL)
	{
		l = find_next_str_node(l);
		merge_with_space(l, str[i]);
		i++;
	}
}

void	set_right_space(t_node *left, t_node *right)
{
	char	**str;

	str = ft_split_quote(right->data.str);
	if (!str)
		return ;
	process_split(left, str);
	free(right->data.str);
	right->data.str = ft_strdup(str[0]);
	ft_free_str(str);
}
