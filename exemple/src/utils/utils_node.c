/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:51:39 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 14:15:31 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_free_node(t_node **node)
{
	if (*node)
	{
		if (((*node)->type) == PAIR_NODE)
		{
			(*node)->data.pair.left = NULL;
			(*node)->data.pair.right = NULL;
			if ((*node)->data.pair.opera)
			{
				free((*node)->data.pair.opera);
				(*node)->data.pair.opera = NULL;
			}
			free(*node);
			*node = NULL;
			return ;
		}
		if ((*node)->data.str)
		{
			if ((*node)->data.str != NULL)
				free((*node)->data.str);
			(*node)->data.str = NULL;
		}
		free(*node);
		*node = NULL;
	}
}

void	ft_free_all_node(t_node **node)
{
	if (!node || !(*node))
		return ;
	if ((*node)->type == STR_NODE)
		ft_free_node(node);
	else
	{
		ft_free_all_node(&(*node)->data.pair.left);
		ft_free_all_node(&(*node)->data.pair.right);
		ft_free_node(node);
	}
}

t_node	*left_before_pipe(t_node *left, t_token **token)
{
	t_node	*l;
	t_token	*tok;

	tok = (*token);
	if (left != NULL)
		tok = tok->prev;
	while (tok->prev != NULL && tok->type != PIPE)
		tok = tok->prev;
	l = str_node(&tok, 0);
	tok = tok->next;
	while (tok && (tok->type != PIPE && tok->type != END_TOKEN))
	{
		if (ft_is_dir(tok) == 1)
			l = pair_node(l, &tok);
		tok = tok->next;
	}
	ft_free_node(&left);
	return (l);
}
