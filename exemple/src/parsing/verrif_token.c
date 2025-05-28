/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verrif_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbutt <hbutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:50:36 by alama             #+#    #+#             */
/*   Updated: 2025/01/08 15:30:23 by hbutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_is_dir(t_token *token)
{
	if ((token->type == PIPE || token->type == O_DIR || token->type == I_DIR
			|| token->type == OA_DIR || token->type == DI_DIR)
		&& token->type != END_TOKEN)
		return (1);
	return (0);
}

static int	first_verrif(t_token *token)
{
	if (token->type == PIPE)
	{
		write(2, "mini-flemme: syntax error near unexpected token `|'\n", 52);
		return (1);
	}
	if (ft_is_dir(token) == 1)
	{
		token = token->next;
		while (token->type == SPACE_TOKEN)
			token = token->next;
		if (token->type == END_TOKEN)
		{
			write(2, "mini-flemme: syntax error near ", 31);
			write(2, "unexpected token `newline'\n", 27);
			return (1);
		}
	}
	return (0);
}

static int	last_verrif(t_token *token)
{
	while (token->type != END_TOKEN)
		token = token->next;
	if (token->type == END_TOKEN)
		token = token->prev;
	while (token->type == SPACE_TOKEN && token->prev != NULL)
		token = token->prev;
	if (token->type == PIPE)
		return (0);
	if (ft_is_dir(token) == 1)
	{
		write(2, "mini-flemme: syntax error near ", 31);
		write(2, "unexpected token `newline'\n", 27);
		return (1);
	}
	return (0);
}

static int	ft_verrif_dir(t_token *tmp)
{
	t_token	*last_dir;

	while (tmp->next->type != END_TOKEN)
	{
		if (ft_is_dir(tmp) == 1)
		{
			last_dir = tmp;
			tmp = tmp->next;
			while (tmp->type == 2)
				tmp = tmp->next;
			if (ft_is_dir(tmp) == 1)
			{
				if (last_dir->type == PIPE && tmp->type != PIPE)
					break ;
				write(2, "mini-flemme: syntax error near ", 31);
				write(2, "unexpected token `", 18);
				write(2, tmp->lexeme, ft_strlen(tmp->lexeme));
				return (write(2, "'\n", 2), 1);
			}
			else
				break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_verrif_tok(t_token **token_list)
{
	t_token	*tmp;

	if (!token_list || !*token_list)
		return (1);
	if (first_verrif(*token_list) == 1)
	{
		ft_free_token(token_list);
		g_excode = 258;
		return (1);
	}
	tmp = *token_list;
	if (ft_verrif_dir(tmp) == 1)
	{
		ft_free_token(token_list);
		g_excode = 258;
		return (1);
	}
	if (last_verrif(tmp) == 1)
	{
		ft_free_token(token_list);
		g_excode = 258;
		return (1);
	}
	return (0);
}
