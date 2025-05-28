/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:36 by alama             #+#    #+#             */
/*   Updated: 2025/01/13 15:51:21 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_node	*pair_dir(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (ft_free_all_node(&left), NULL);
	new_node->data.pair.opera = ft_strdup((*token)->lexeme);
	if ((*token)->type == DI_DIR)
		heredoc_parse(token);
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	*token = (*token)->next;
	while ((*token)->type == SPACE_TOKEN)
		*token = (*token)->next;
	right = str_node(token, 0);
	if (!right)
	{
		ft_free_node(&new_node);
		return (ft_free_all_node(&left), NULL);
	}
	set_right_space(left, right);
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*one_str(t_token **token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = STR_NODE;
	if (!token || (*token)->type == END_TOKEN)
		node->data.str = ft_strdup("");
	else
	{
		while ((*token)->type == SPACE_TOKEN)
			*token = (*token)->next;
		if (ft_is_dir(*token) == 0)
		{
			node->data.str = ft_strdup((*token)->lexeme);
			*token = (*token)->next;
		}
		else
		{
			node->data.str = ft_strdup("");
			*token = (*token)->prev;
		}
	}
	return (node);
}

t_node	*weird_dir(t_token **token)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data.pair.opera = ft_strdup((*token)->lexeme);
	if ((*token)->type == DI_DIR)
		heredoc_parse(token);
	*token = (*token)->next;
	new_node->data.pair.right = one_str(token);
	if (!new_node->data.pair.right)
		return (ft_free_all_node(&new_node), NULL);
	new_node->data.pair.left = str_node(token, 0);
	if (!new_node->data.pair.left)
	{
		new_node->data.pair.left = one_str(NULL);
		if (ft_is_dir(*token) == 1)
			*token = (*token)->prev;
	}
	if (!new_node->data.pair.left)
		return (ft_free_all_node(&new_node), NULL);
	if ((*token)->type == END_TOKEN)
		*token = (*token)->prev;
	return (new_node);
}

t_node	*dir_parse(t_token **token)
{
	t_node	*left;

	while ((*token)->type == SPACE_TOKEN && (*token)->next->type != END_TOKEN)
		*token = (*token)->next;
	left = str_node(token, 0);
	while (token && *token && (*token)->type != PIPE
		&& (*token)->type != END_TOKEN)
	{
		if (ft_is_dir(*token) == 1)
		{
			if (!left)
				left = weird_dir(token);
			else
				left = pair_dir(left, token);
			if (!left)
				return (NULL);
		}
		if ((*token)->type != END_TOKEN)
			*token = (*token)->next;
	}
	return (left);
}
