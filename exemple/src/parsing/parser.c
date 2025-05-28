/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:37:20 by alama             #+#    #+#             */
/*   Updated: 2025/01/15 16:24:03 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	add_lexeme_to_node(t_token **token, t_node *node, int pipe)
{
	char	*str;

	str = NULL;
	if (ft_is_dir((*token)) == 1)
	{
		node = one_str(NULL);
		return ;
	}
	if (pipe == 1)
		return ;
	node->data.str = ft_strdup((*token)->lexeme);
	while (ft_is_dir(*token) == 0 && ((*token)->next->type != END_TOKEN
			&& ft_is_dir((*token)->next) == 0))
	{
		if ((*token)->next->type == SPACE_TOKEN
			&& ft_is_dir((*token)->next->next) == 1)
			break ;
		str = ft_strjoin(node->data.str, (*token)->next->lexeme);
		free(node->data.str);
		node->data.str = ft_strdup(str);
		free(str);
		*token = (*token)->next;
	}
}

t_node	*str_node(t_token **token, int pipe)
{
	t_node	*node;

	if (!token || (*token)->type == END_TOKEN || ft_is_dir(*token) == 1)
		return (NULL);
	while ((*token)->type == SPACE_TOKEN)
		*token = (*token)->next;
	if (ft_is_dir(*token) == 1)
	{
		return (NULL);
	}
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = STR_NODE;
	add_lexeme_to_node(token, node, pipe);
	return (node);
}

t_node	*pair_node(t_node *left, t_token **token)
{
	t_node	*new_node;
	t_node	*right;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (ft_free_all_node(&left), NULL);
	new_node->data.pair.opera = ft_strdup((*token)->lexeme);
	*token = (*token)->next;
	new_node->type = PAIR_NODE;
	new_node->data.pair.left = left;
	right = dir_parse(token);
	if (!right)
	{
		ft_free_node(&new_node);
		return (ft_free_all_node(&left), NULL);
	}
	new_node->data.pair.right = right;
	return (new_node);
}

t_node	*parse(t_token **token_list)
{
	t_token	*token;
	t_node	*left;

	token = (*token_list);
	left = NULL;
	left = dir_parse(&token);
	if (left == NULL)
		exit(12);
	while (token && token->type != END_TOKEN)
	{
		if (token->type == PIPE)
		{
			left = pair_node(left, &token);
			if (!left)
				exit(12);
			token = token->prev;
		}
		token = token->next;
	}
	return (left);
}

void	print_node(t_node *node)
{
	if (node->type == STR_NODE)
		printf("node : %s\n", node->data.str);
	else
	{
		printf("operator : %s\n", node->data.pair.opera);
		if (node->data.pair.left)
		{
			printf("left ");
			print_node(node->data.pair.left);
		}
		if (node->data.pair.right)
		{
			printf("right ");
			print_node(node->data.pair.right);
		}
	}
}
