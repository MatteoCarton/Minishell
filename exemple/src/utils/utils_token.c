/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:33:46 by hbutt             #+#    #+#             */
/*   Updated: 2025/01/17 13:02:15 by alama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	ft_add_next(t_token *last, t_token **token_list, t_token *new_node)
{
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	(*token_list)->prev = new_node;
}

static void	ft_del(t_token *token)
{
	if (token)
	{
		token->next = NULL;
		token->prev = NULL;
		free(token->lexeme);
		token->lexeme = NULL;
		free(token);
	}
}

void	ft_free_token(t_token **token_list)
{
	t_token	*tmp;

	if (!token_list || !(*token_list))
		return ;
	while (*token_list)
	{
		tmp = (*token_list)->next;
		ft_del(*token_list);
		*token_list = tmp;
	}
	token_list = NULL;
}

t_token	*last_token(t_token *token)
{
	while (token->type != END_TOKEN)
		token = token->next;
	return (token);
}

void	remove_end(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	tmp = last_token(tmp);
	tmp = tmp->prev;
	free(tmp->next->lexeme);
	free(tmp->next);
	tmp->next = NULL;
}
