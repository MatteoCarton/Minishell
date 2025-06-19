/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:53:22 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/17 16:58:40 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
}

void	clean_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
	{
		free(token->str);
		token->str = NULL;
	}
	token->next = NULL;
	token->type = 0;
}

void	free_token(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		clean_token(current);
		free(current);
		current = next;
	}
	*head = NULL;
}

/*pour printf les token test*/
void	printoken(t_token *head)
{
	t_token		*actual;

	actual = head;
	while (actual)
	{
		printf("type: %d, value: %s\n", actual->type, actual->str);
		actual = actual->next;
	}
}
